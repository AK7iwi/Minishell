/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/11 12:22:51 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nMinishell> ", 12);
}

static void handle_sigquit(int sig)
{
    (void)sig;
}
static void handle_signals()
{
	signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit); 
}
static bool is_arg(t_error *error, int argc)
{
	if (argc != 1)
		return (error->gen_errors |= ERROR_ARG, true);

	return (false);
}
int main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;
	
	if (init(&data, argv, envp) || is_arg(&data.error, argc))
		return (errors_displayer(data.error), EXIT_FAILURE);
	
	handle_signals();
	
    while (true)
    {
        input = readline("Minishell> ");
		if (!input)
		{
			printf("exit\n");
			return (free_all(&data), EXIT_FAILURE);
		}
        if (tokenizer(&data, input) || syn_analyzer(&data) || ast_creator(&data))
			errors_displayer(data.error);
		else if (ast_exec(&data, data.ast))
			errors_displayer(data.error);
		
		free_loop(&data);
    }
	
    return (EXIT_SUCCESS);
}
