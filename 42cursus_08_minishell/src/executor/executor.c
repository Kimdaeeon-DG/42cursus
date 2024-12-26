#include "../../includes/minishell.h"

void print_error(char *cmd, char *msg)
{
    fprintf(stderr, "minishell: %s: %s\n", cmd, msg);
}

int is_builtin(char *cmd)
{
    return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
            !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
            !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
            !ft_strcmp(cmd, "exit"));
}

int execute_builtin(char **args, t_env *env)
{
    if (!ft_strcmp(args[0], "echo"))
        return (ft_echo(args));
    else if (!ft_strcmp(args[0], "cd"))
        return (ft_cd(args, env));
    else if (!ft_strcmp(args[0], "pwd"))
        return (ft_pwd());
    else if (!ft_strcmp(args[0], "export"))
        return (ft_export(args, env));
    else if (!ft_strcmp(args[0], "unset"))
        return (ft_unset(args, env));
    else if (!ft_strcmp(args[0], "env"))
        return (ft_env(env));
    else if (!ft_strcmp(args[0], "exit"))
        return (ft_exit(args));
    return (1);
}

char *find_command_path(char *cmd, t_env *env)
{
    char *path_env;
    char *path;
    char *full_path;
    char *dir;
    char *temp;

    if (cmd[0] == '/' || cmd[0] == '.')
        return (ft_strdup(cmd));

    path_env = get_env(env, "PATH");
    if (!path_env)
        return (NULL);

    path = ft_strdup(path_env);
    dir = strtok(path, ":");

    while (dir)
    {
        temp = ft_strjoin(dir, "/");
        full_path = ft_strjoin(temp, cmd);
        free(temp);

        if (access(full_path, X_OK) == 0)
        {
            free(path);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path);
    return (NULL);
}

int setup_redirections(t_cmd *cmd)
{
    int fd;

    if (cmd->input_file)
    {
        fd = open(cmd->input_file, O_RDONLY);
        if (fd == -1)
        {
            print_error(cmd->input_file, strerror(errno));
            return (0);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (cmd->output_file)
    {
        fd = open(cmd->output_file,
                 O_WRONLY | O_CREAT | (cmd->append_mode ? O_APPEND : O_TRUNC),
                 0644);
        if (fd == -1)
        {
            print_error(cmd->output_file, strerror(errno));
            return (0);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    return (1);
}

void restore_redirections(int stdin_backup, int stdout_backup)
{
    dup2(stdin_backup, STDIN_FILENO);
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdin_backup);
    close(stdout_backup);
}

char **env_to_array(t_env *env)
{
    int count;
    char **arr;
    t_env *current;
    char *temp;
    int i;

    count = 0;
    current = env;
    while (current)
    {
        count++;
        current = current->next;
    }

    arr = malloc(sizeof(char *) * (count + 1));
    if (!arr)
        return (NULL);

    i = 0;
    current = env;
    while (current)
    {
        temp = ft_strjoin(current->key, "=");
        arr[i] = ft_strjoin(temp, current->value);
        free(temp);
        current = current->next;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

static int execute_single_command(t_cmd *cmd, t_env *env)
{
    pid_t pid;
    int status;
    char *cmd_path;
    char **envp;

    if (!cmd->args || !cmd->args[0])
        return (0);

    if (is_builtin(cmd->args[0]))
        return (execute_builtin(cmd->args, env));

    cmd_path = find_command_path(cmd->args[0], env);
    if (!cmd_path)
    {
        print_error(cmd->args[0], "command not found");
        return (127);
    }

    pid = fork();
    if (pid == 0)
    {
        if (!setup_redirections(cmd))
            exit(1);

        envp = env_to_array(env);
        execve(cmd_path, cmd->args, envp);
        print_error(cmd->args[0], strerror(errno));
        exit(1);
    }
    else if (pid < 0)
    {
        print_error(cmd->args[0], "fork failed");
        free(cmd_path);
        return (1);
    }

    free(cmd_path);
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}

static int execute_pipe(t_cmd *cmd1, t_cmd *cmd2, t_env *env)
{
    int pipefd[2];
    pid_t pid1, pid2;
    int status;

    if (pipe(pipefd) == -1)
    {
        print_error("pipe", strerror(errno));
        return (1);
    }

    pid1 = fork();
    if (pid1 == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (!setup_redirections(cmd1))
            exit(1);

        if (is_builtin(cmd1->args[0]))
            exit(execute_builtin(cmd1->args, env));
        else
        {
            char *cmd_path = find_command_path(cmd1->args[0], env);
            if (!cmd_path)
            {
                print_error(cmd1->args[0], "command not found");
                exit(127);
            }
            execve(cmd_path, cmd1->args, env_to_array(env));
            print_error(cmd1->args[0], strerror(errno));
            exit(1);
        }
    }

    pid2 = fork();
    if (pid2 == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        if (!setup_redirections(cmd2))
            exit(1);

        if (is_builtin(cmd2->args[0]))
            exit(execute_builtin(cmd2->args, env));
        else
        {
            char *cmd_path = find_command_path(cmd2->args[0], env);
            if (!cmd_path)
            {
                print_error(cmd2->args[0], "command not found");
                exit(127);
            }
            execve(cmd_path, cmd2->args, env_to_array(env));
            print_error(cmd2->args[0], strerror(errno));
            exit(1);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    return (WEXITSTATUS(status));
}

int execute_pipeline(t_cmd *cmd, t_env *env)
{
    t_cmd *current;
    t_cmd *next;
    int status;

    current = cmd;
    while (current && current->next)
    {
        next = current->next;
        status = execute_pipe(current, next, env);
        current = next->next;
    }

    return (status);
}

int execute_commands(t_cmd *cmd, t_env *env)
{
    int stdin_backup;
    int stdout_backup;
    int status;

    if (!cmd)
        return (0);

    stdin_backup = dup(STDIN_FILENO);
    stdout_backup = dup(STDOUT_FILENO);

    if (cmd->next)
        status = execute_pipeline(cmd, env);
    else
        status = execute_single_command(cmd, env);

    restore_redirections(stdin_backup, stdout_backup);
    return (status);
}
