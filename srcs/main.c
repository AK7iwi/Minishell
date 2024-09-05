/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/05 17:20:34 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token_list(t_token *head)
{
    t_token *current = head;
		
    while (current)
    {
        printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
        current = current->next;
    }
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
    (void)envp; //tmp

	t_data	data;
	char *input;

    if (argc != 1)
    {
        printf("Get your arguments out of the way");
        return (EXIT_FAILURE);
    }
	
	init_struct(&data);
	
    while (1)
    {
        input = readline("Minishell> ");
		if (!input)
			return (free_all(&data), EXIT_FAILURE);

		//add_to_history
        tokenisation(input, &data.token);
		print_token_list(data.token);
		// free(input);
    	free_token(&data.token);
    }

	free_all(&data);
	
    return (EXIT_SUCCESS);
}