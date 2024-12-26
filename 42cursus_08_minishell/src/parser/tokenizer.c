#include "../../includes/minishell.h"

static t_token *create_token(t_token_type type, char *value)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value;
    token->next = NULL;
    return (token);
}

static void add_token(t_token **tokens, t_token *new_token)
{
    t_token *current;

    if (!*tokens)
    {
        *tokens = new_token;
        return;
    }
    current = *tokens;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

static int is_operator_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static char *get_word(char **input)
{
    char *start;
    char *word;
    int len;
    char quote;
    int in_quote;

    start = *input;
    len = 0;
    in_quote = 0;
    quote = 0;

    while (**input)
    {
        if (!in_quote && (**input == '\'' || **input == '\"'))
        {
            in_quote = 1;
            quote = **input;
        }
        else if (in_quote && **input == quote)
        {
            in_quote = 0;
            quote = 0;
        }
        else if (!in_quote && (is_whitespace(**input) || is_operator_char(**input)))
            break;
        (*input)++;
        len++;
    }

    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    strncpy(word, start, len);
    word[len] = '\0';
    return (word);
}

static t_token_type get_operator_type(char **input)
{
    if (**input == '|')
    {
        (*input)++;
        return (TOKEN_PIPE);
    }
    else if (**input == '<')
    {
        (*input)++;
        if (**input == '<')
        {
            (*input)++;
            return (TOKEN_HEREDOC);
        }
        return (TOKEN_REDIR_IN);
    }
    else if (**input == '>')
    {
        (*input)++;
        if (**input == '>')
        {
            (*input)++;
            return (TOKEN_REDIR_APPEND);
        }
        return (TOKEN_REDIR_OUT);
    }
    return (TOKEN_WORD);
}

t_token *tokenize(char *input)
{
    t_token *tokens;
    t_token *new_token;
    t_token_type type;

    tokens = NULL;
    while (*input)
    {
        while (is_whitespace(*input))
            input++;
        if (!*input)
            break;

        if (is_operator_char(*input))
        {
            type = get_operator_type(&input);
            new_token = create_token(type, NULL);
        }
        else
        {
            new_token = create_token(TOKEN_WORD, get_word(&input));
        }
        
        if (new_token)
            add_token(&tokens, new_token);
    }
    add_token(&tokens, create_token(TOKEN_EOF, NULL));
    return (tokens);
}

void free_tokens(t_token *tokens)
{
    t_token *current;
    t_token *next;

    current = tokens;
    while (current)
    {
        next = current->next;
        if (current->value)
            free(current->value);
        free(current);
        current = next;
    }
}

char *expand_variables(char *str, t_env *env)
{
    char *result;
    char *temp;
    char *value;
    int i;
    int j;

    result = malloc(strlen(str) * 2);  // 충분한 공간 할당
    if (!result)
        return (NULL);

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1])
        {
            i++;
            temp = malloc(strlen(str));
            if (!temp)
            {
                free(result);
                return (NULL);
            }

            int k = 0;
            while (str[i] && (isalnum(str[i]) || str[i] == '_'))
                temp[k++] = str[i++];
            temp[k] = '\0';

            value = get_env(env, temp);
            free(temp);

            if (value)
            {
                strcpy(result + j, value);
                j += strlen(value);
            }
        }
        else
            result[j++] = str[i++];
    }
    result[j] = '\0';

    return (result);
}
