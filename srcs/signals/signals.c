/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:00:55 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/05 09:54:54 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_server(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
    	rl_on_new_line();
    	//rl_replace_line("", 0);
    	rl_redisplay(); 
	}
}

void signals(void)
{
	struct sigaction	act;
	
	act.sa_sigaction = signal_handler_server;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}