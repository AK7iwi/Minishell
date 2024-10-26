/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:02:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/26 10:30:38 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool syn_analyzer(t_data *data)
{
    t_token		*current;
	uint32_t	o_counter;
	uint32_t	c_counter;
	
	o_counter = 0;
	c_counter = 0;
    current = data->token;
	
    while (current)
    {
		if (check_operator(current))
			return (data->error.parsing_errors |= ERROR_OPERATOR, EXIT_FAILURE);
		else if (check_redir(current))
			return (data->error.parsing_errors |= ERROR_REDIR, EXIT_FAILURE);	
		else if (check_paren(current, &o_counter, &c_counter))
			return (data->error.parsing_errors |= ERROR_PARAN, EXIT_FAILURE);
		current = current->next;
    }
	
	if (o_counter != c_counter)
		return (data->error.parsing_errors |= ERROR_PARAN, EXIT_FAILURE);
	
    return (EXIT_SUCCESS);
}


