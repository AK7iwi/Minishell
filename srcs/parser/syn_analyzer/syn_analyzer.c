/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:02:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/14 12:38:45 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syn_analyzer(t_data *data)
{
    t_tok		*current;
	uint32_t	o_count;
	uint32_t	c_count;
	
	o_count = 0;
	c_count = 0;
    current = data->tok;
	
    while (current)
    {
		if (check_paren(&data->err, current, &o_count, &c_count))
			return (data->err.parsing_errors |= ERR_PARAN, EXIT_FAILURE);
		else if (check_operator(&data->err, current))
			return (data->err.parsing_errors |= ERR_OPERATOR, EXIT_FAILURE);
		else if (check_redir(&data->err, current))
			return (data->err.parsing_errors |= ERR_REDIR, EXIT_FAILURE);
		current = current->next;
    }
	
	if (o_count != c_count) // display_error
		return (data->err.parsing_errors |= ERR_PARAN, EXIT_FAILURE);
	
    return (EXIT_SUCCESS);
}


