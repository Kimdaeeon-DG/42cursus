#include "../../includes/minishell.h"

static t_cmd *create_cmd(void)
{
    t_cmd *cmd;

    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_mode = 0;
    cmd->next = NULL;
    return (cmd);
}

static void add_arg(t_cmd *cmd, char *arg)
{
    char **new_args;
    int i;
    int size;

    size = 0;
    if (cmd->args)
    {
        while (cmd->args[size])
            size++;
    }

    new_args = (char **)malloc(sizeof(char *) * (size + 2));
    if (!new_args)
        return;

    i = 0;
    while (i < size)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[i] = arg;
    new_args[i + 1] = NULL;

    if (cmd->args)
        free(cmd->args);
    cmd->args = new_args;
}

static int handle_redirection(t_cmd *cmd, t_token **tokens)
{
    t_token_type type;
    char *filename;

    type = (*tokens)->type;
    *tokens = (*tokens)->next;
    
    if ((*tokens)->type != TOKEN_WORD)
        return (0);
    
    filename = (*tokens)->value;
    *tokens = (*tokens)->next;

    if (type == TOKEN_REDIR_IN)
    {
        if (cmd->input_file)
            free(cmd->input_file);
        cmd->input_file = ft_strdup(filename);
    }
    else if (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_APPEND)
    {
        if (cmd->output_file)
            free(cmd->output_file);
        cmd->output_file = ft_strdup(filename);
        cmd->append_mode = (type == TOKEN_REDIR_APPEND);
    }
    return (1);
}

t_cmd *parse_pipeline(t_token **tokens)
{
    t_cmd *cmd;
    t_cmd *pipeline;

    pipeline = NULL;
    cmd = create_cmd();
    if (!cmd)
        return (NULL);

    while (*tokens && (*tokens)->type != TOKEN_EOF)
    {
        if ((*tokens)->type == TOKEN_WORD)
        {
            add_arg(cmd, ft_strdup((*tokens)->value));
            *tokens = (*tokens)->next;
        }
        else if ((*tokens)->type == TOKEN_PIPE)
        {
            if (!pipeline)
                pipeline = cmd;
            else
            {
                t_cmd *current = pipeline;
                while (current->next)
                    current = current->next;
                current->next = cmd;
            }
            *tokens = (*tokens)->next;
            cmd = create_cmd();
            if (!cmd)
                return (NULL);
        }
        else if ((*tokens)->type >= TOKEN_REDIR_IN && (*tokens)->type <= TOKEN_HEREDOC)
        {
            if (!handle_redirection(cmd, tokens))
                return (NULL);
        }
        else
            return (NULL);
    }

    if (!pipeline)
        pipeline = cmd;
    else
    {
        t_cmd *current = pipeline;
        while (current->next)
            current = current->next;
        current->next = cmd;
    }

    return (pipeline);
}

t_cmd *parse_input(char *input, t_env *env)
{
    t_token *tokens;
    t_cmd *cmd;
    char *expanded_input;

    expanded_input = expand_variables(input, env);
    if (!expanded_input)
        return (NULL);

    tokens = tokenize(expanded_input);
    free(expanded_input);
    if (!tokens)
        return (NULL);

    cmd = parse_pipeline(&tokens);
    free_tokens(tokens);
    return (cmd);
}

void free_cmd(t_cmd *cmd)
{
    t_cmd *current;
    t_cmd *next;
    int i;

    current = cmd;
    while (current)
    {
        next = current->next;
        
        if (current->args)
        {
            i = 0;
            while (current->args[i])
            {
                free(current->args[i]);
                i++;
            }
            free(current->args);
        }
        
        if (current->input_file)
            free(current->input_file);
        if (current->output_file)
            free(current->output_file);
        
        free(current);
        current = next;
    }
}
