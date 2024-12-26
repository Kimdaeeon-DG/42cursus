#include "../includes/minishell.h"

static void handle_input(char *input, t_env *env)
{
    t_cmd *cmd;

    if (!input) // Ctrl+D (EOF)
    {
        printf("\nexit\n");
        exit(g_exit_status);
    }
    if (*input)
    {
        add_history(input);
        cmd = parse_input(input, env);
        if (cmd)
        {
            g_exit_status = execute_commands(cmd, env);
            free_cmd(cmd);
        }
    }
    free(input);
}

int main(int argc, char **argv, char **envp)
{
    t_env *env;
    char *input;

    (void)argc;
    (void)argv;

    env = init_env(envp);
    setup_signals();

    while (1)
    {
        input = readline(PROMPT);
        handle_input(input, env);
    }

    free_env(env);
    return (g_exit_status);
}
