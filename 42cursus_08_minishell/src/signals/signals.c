#include "../../includes/minishell.h"

int g_exit_status = 0;

void handle_sigint(int sig)
{
    (void)sig;
    g_exit_status = 130;
    printf("\n");
    rl_on_new_line();
    rl_redisplay();
}

void handle_sigquit(int sig)
{
    (void)sig;
}

void handle_child_sigint(int sig)
{
    (void)sig;
    printf("\n");
}

void handle_child_sigquit(int sig)
{
    (void)sig;
    printf("Quit: %d\n", sig);
}

void setup_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sigemptyset(&sa_int.sa_mask);
    sigemptyset(&sa_quit.sa_mask);
    sa_int.sa_flags = 0;
    sa_quit.sa_flags = 0;

    sa_int.sa_handler = handle_sigint;
    sa_quit.sa_handler = handle_sigquit;

    sigaction(SIGINT, &sa_int, NULL);   /* Ctrl+C */
    sigaction(SIGQUIT, &sa_quit, NULL); /* Ctrl+\ */
}

void setup_child_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sigemptyset(&sa_int.sa_mask);
    sigemptyset(&sa_quit.sa_mask);
    sa_int.sa_flags = 0;
    sa_quit.sa_flags = 0;

    sa_int.sa_handler = handle_child_sigint;
    sa_quit.sa_handler = handle_child_sigquit;

    sigaction(SIGINT, &sa_int, NULL);   /* Ctrl+C */
    sigaction(SIGQUIT, &sa_quit, NULL); /* Ctrl+\ */
}
