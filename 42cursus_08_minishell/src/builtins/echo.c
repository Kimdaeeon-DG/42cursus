#include "../../includes/minishell.h"

int ft_echo(char **args)
{
    int i;
    int n_flag;

    n_flag = 0;
    i = 1;
    
    // Check for -n option
    if (args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        n_flag = 1;
        i++;
    }

    // Print arguments
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    
    // Print newline if -n flag is not set
    if (!n_flag)
        printf("\n");
    
    return (0);
}
