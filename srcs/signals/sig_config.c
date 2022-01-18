#include "../../minishell.h"

void signal_handler(int sig)
{
	if (sig == SIGQUIT)
		write(1, "\033[2D\033[OK", 8);
	if (sig == SIGINT)
		printf("PROUT\n");
}

void	sig_config(void)
{
	struct sigaction 	intact;
	struct sigaction 	quitact;

	intact.sa_handler = signal_handler;
	quitact.sa_handler = signal_handler;
	sigaction(SIGINT, &intact, NULL);
	sigaction(SIGQUIT, &quitact, NULL);
}
