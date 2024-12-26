#include "../../includes/minishell.h"

int ft_pwd(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
        return (0);
    }
    else
    {
        printf("pwd: %s\n", strerror(errno));
        return (1);
    }
}
