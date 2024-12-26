#include "../../includes/minishell.h"

t_env *init_env(char **envp)
{
    t_env *env;
    t_env *new;
    char *equal_sign;
    int i;

    env = NULL;
    i = 0;
    while (envp[i])
    {
        equal_sign = strchr(envp[i], '=');
        if (equal_sign)
        {
            *equal_sign = '\0';
            new = (t_env *)malloc(sizeof(t_env));
            if (!new)
                return (NULL);
            new->key = ft_strdup(envp[i]);
            new->value = ft_strdup(equal_sign + 1);
            new->next = env;
            env = new;
            *equal_sign = '=';
        }
        i++;
    }
    return (env);
}

void add_env(t_env **env, char *key, char *value)
{
    t_env *current;
    t_env *new;

    current = *env;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }

    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return;
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = *env;
    *env = new;
}

char *get_env(t_env *env, char *key)
{
    t_env *current;

    current = env;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

void free_env(t_env *env)
{
    t_env *current;
    t_env *next;

    current = env;
    while (current)
    {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}
