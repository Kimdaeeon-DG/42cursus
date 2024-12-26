#include "../../includes/minishell.h"

static int is_valid_identifier(char *str)
{
    int i;

    if (!str || !*str || (!(*str >= 'a' && *str <= 'z') && 
        !(*str >= 'A' && *str <= 'Z') && *str != '_'))
        return (0);
    
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || 
            (str[i] >= 'A' && str[i] <= 'Z') || 
            (str[i] >= '0' && str[i] <= '9') || 
            str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

static void export_variable(char *arg, t_env *env)
{
    char *key;
    char *value;
    char *equal_sign;

    equal_sign = strchr(arg, '=');
    if (!equal_sign)
    {
        // If no value is provided, set empty string as value
        key = ft_strdup(arg);
        value = ft_strdup("");
    }
    else
    {
        *equal_sign = '\0';
        key = ft_strdup(arg);
        value = ft_strdup(equal_sign + 1);
        *equal_sign = '=';
    }

    if (is_valid_identifier(key))
        add_env(&env, key, value);
    else
        printf("export: '%s': not a valid identifier\n", key);

    free(key);
    free(value);
}

int ft_export(char **args, t_env *env)
{
    t_env *current;
    int i;

    if (!args[1])
    {
        // Print all environment variables in export format
        current = env;
        while (current)
        {
            printf("declare -x %s=\"%s\"\n", current->key, current->value);
            current = current->next;
        }
        return (0);
    }

    i = 1;
    while (args[i])
    {
        export_variable(args[i], env);
        i++;
    }
    return (0);
}
