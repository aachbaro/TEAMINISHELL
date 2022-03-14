/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:00:42 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/14 22:25:27 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 
 * signal configuration
 * here we setup the signal action and signal handler
 * CTRL-c is SIGINT
 * CTRL-\ is SIGQUIT
 * CTRL-d is not a signal but rather send an EOF 
 */
void	handle_int(int sig)
{
	if (g_g.status == 1)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		g_g.exit = 128 + sig;
		return ;
	}
	else if (g_g.status == 2)
	{
		rl_clear_history();
		g_g.exit = 128 + sig;
		free_all(g_g.data);
		//ft_putchar_fd('\n', STDIN_FILENO);
		//ft_putchar_fd('\n', STDIN_FILENO);
		//exit(g_g.exit);
	}
	else if (g_g.status == 3)
		return ;
	else if (g_g.status == 0)
	{
		g_g.exit = 128 + sig;
		ft_putchar_fd('\n', STDIN_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		handle_int(sig);
	if (sig == SIGQUIT)
	{
		if (g_g.status == 1)
			ft_putstr_fd("Quit (core dumped)\n", STDIN_FILENO);
		else if (g_g.status == 3 || g_g.status == 0)
			return ;
	}
}

void	sig_config(void)
{
	struct sigaction	quitact;

	quitact.sa_handler = signal_handler;
	quitact.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &quitact, NULL);
}
