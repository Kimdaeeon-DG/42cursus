#include "../../includes/minishell.h"

static void update_pwd_env(t_env *env)
{
    char cwd[1024];
    char *old_pwd;

    old_pwd = get_env(env, "PWD");
    if (old_pwd)
        add_env(&env, "OLDPWD", old_pwd);
    
    if (getcwd(cwd, sizeof(cwd)))
        add_env(&env, "PWD", cwd);
}

int ft_cd(char **args, t_env *env)
{
    char *path;

    // If no argument is given, change to HOME directory
    if (!args[1])
    {
        path = get_env(env, "HOME");
        if (!path)
        {
            printf("cd: HOME not set\n");
            return (1);
        }
    }
    // If argument is "-", change to OLDPWD
    else if (ft_strcmp(args[1], "-") == 0)
    {
        path = get_env(env, "OLDPWD");
        if (!path)
        {
            printf("cd: OLDPWD not set\n");
            return (1);
        }
        printf("%s\n", path);
    }
    else
        path = args[1];

    if (chdir(path) == -1)
    {
        printf("cd: %s: %s\n", path, strerror(errno));
        return (1);
    }

    update_pwd_env(env);
    return (0);
}
