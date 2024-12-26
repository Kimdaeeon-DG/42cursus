#include "../../includes/minishell.h"

int ft_env(t_env *env)
{
    t_env *current;

    current = env;
    while (current)
    {
        if (current->value && *(current->value))
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return (0);
}
