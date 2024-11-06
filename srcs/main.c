/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/06 14:40:43 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_arg(t_error *error, int argc) // in tools
{
	if (argc != 1)
		return (error->gen_errors |= ERR_ARG, true);

	return (false);
}
int main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;
	
	signals();
	if (init(&data, argv, envp) || is_arg(&data.error, argc))
		return (errors_displayer(data.error), free_all(&data), EXIT_FAILURE);
	
    while (true)
    {
        input = readline("mimishell. ");
		if (!input)
			return (printf("exit\n"), free_all(&data), EXIT_FAILURE); //ft_exit
		add_history(input);
		
        if (tokenizer(&data, input) || syn_analyzer(&data)
				|| ast_creator(&data) || exec(&data, data.ast))
			errors_displayer(data.error);
		
		// print_token(data.token);
		free_loop(&data);
    }
    return (EXIT_SUCCESS);
}