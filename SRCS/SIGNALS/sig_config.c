#include "../../minishell.h"

void sigint_handler(int)
{
	write(1, "\n", 1);
	prompt(NULL);
}

void quitact_handler(int)
{
	write(1, "", 1);
}

void	sig_config(void)
{
	struct sigaction 	intact;
	struct sigaction 	quitact;

	intact.sa_handler = sigint_handler;
	quitact.sa_handler = quitact_handler;
	sigaction(SIGINT, &intact, NULL);
	sigaction(SIGQUIT, &quitact, NULL);
}
