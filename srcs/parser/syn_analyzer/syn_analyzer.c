/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:02:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:11:31 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool syn_analyzer(t_data *data)
{
    t_tok		*current;
	uint32_t	o_counter;
	uint32_t	c_counter;
	
	o_counter = 0;
	c_counter = 0;
    current = data->tok;
	
    while (current)
    {
		if (check_operator(current))
			return (data->err.parsing_errors |= ERR_OPERATOR, EXIT_FAILURE);
		else if (check_redir(current))
			return (data->err.parsing_errors |= ERR_REDIR, EXIT_FAILURE);
		else if (check_paren(current, &o_counter, &c_counter))
			return (data->err.parsing_errors |= ERR_PARAN, EXIT_FAILURE);
		current = current->next;
    }
	
	if (o_counter != c_counter)
		return (data->err.parsing_errors |= ERR_PARAN, EXIT_FAILURE);
	
    return (EXIT_SUCCESS);
}


