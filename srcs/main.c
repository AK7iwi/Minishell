/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/06 10:52:47 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	
	signals();
    while (true)
    {
        input = readline("Minishell> ");
		if (!input)
			return (printf("exit\n"), free_all(&data), EXIT_FAILURE); //ft_exit
		add_history(input);
		
        if (tokenizer(&data, input) || syn_analyzer(&data)
				|| ast_creator(&data) || exec(&data, data.ast))
			errors_displayer(data.error);
		
		print_token(data.token);
		free_loop(&data);
    }
    return (EXIT_SUCCESS);
}