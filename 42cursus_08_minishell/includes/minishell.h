#ifndef MINISHELL_H
# define MINISHELL_H

/* Required for readline */
# define _GNU_SOURCE

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <ctype.h>

# define PROMPT "minishell$ "

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC,
    TOKEN_EOF
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

typedef struct s_cmd
{
    char **args;
    char *input_file;
    char *output_file;
    int append_mode;
    struct s_cmd *next;
} t_cmd;

/* Environment functions */
t_env *init_env(char **envp);
void add_env(t_env **env, char *key, char *value);
char *get_env(t_env *env, char *key);
void free_env(t_env *env);

/* Builtin commands */
int ft_echo(char **args);
int ft_cd(char **args, t_env *env);
int ft_pwd(void);
int ft_export(char **args, t_env *env);
int ft_unset(char **args, t_env *env);
int ft_env(t_env *env);
int ft_exit(char **args);

/* Tokenizer functions */
t_token *tokenize(char *input);
void free_tokens(t_token *tokens);
char *expand_variables(char *str, t_env *env);

/* Parser functions */
t_cmd *parse_input(char *input, t_env *env);
t_cmd *parse_pipeline(t_token **tokens);
void free_cmd(t_cmd *cmd);

/* Executor functions */
int execute_commands(t_cmd *cmd, t_env *env);
int execute_builtin(char **args, t_env *env);
int is_builtin(char *cmd);
char *find_command_path(char *cmd, t_env *env);
int setup_redirections(t_cmd *cmd);
void restore_redirections(int stdin_backup, int stdout_backup);
int execute_pipeline(t_cmd *cmd, t_env *env);
char **env_to_array(t_env *env);

/* Error handling */
void print_error(char *cmd, char *msg);

/* Utils functions */
char *ft_strdup(const char *s);
char **ft_split(char const *s, char c);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strjoin(char const *s1, char const *s2);

/* Global variable for exit status */
extern int g_exit_status;

/* Signal handling */
void setup_signals(void);
void handle_sigint(int sig);
void handle_sigquit(int sig);
void setup_child_signals(void);

#endif
