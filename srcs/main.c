/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/20 13:09:03 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
    // // rl_replace_line("", 0); 
    rl_redisplay(); 
}
void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0); 
    rl_redisplay(); 
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
	
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	
    while (true)
    {
        input = readline("Minishell> ");
		if (!input)
			return (printf("exit\n"), free_all(&data), EXIT_FAILURE);
		add_history(input);
		
        if (tokenizer(&data, input) || syn_analyzer(&data)
				|| ast_creator(&data) || exec(&data, data.ast))
			errors_displayer(data.error);
		
		free_loop(&data);
    }
    return (EXIT_SUCCESS);
}
