#include "../../includes/minishell.h"

static int is_numeric(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int ft_exit(char **args)
{
    int exit_code;

    printf("exit\n");
    
    if (!args[1])
        exit(0);

    if (!is_numeric(args[1]))
    {
        printf("exit: %s: numeric argument required\n", args[1]);
        exit(255);
    }

    if (args[2])
    {
        printf("exit: too many arguments\n");
        return (1);
    }

    exit_code = atoi(args[1]);
    exit(exit_code % 256);
}
