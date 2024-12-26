#include "../../includes/minishell.h"

static void remove_env(t_env **env, char *key)
{
    t_env *current;
    t_env *prev;

    current = *env;
    prev = NULL;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int ft_unset(char **args, t_env *env)
{
    int i;

    i = 1;
    while (args[i])
    {
        remove_env(&env, args[i]);
        i++;
    }
    return (0);
}
