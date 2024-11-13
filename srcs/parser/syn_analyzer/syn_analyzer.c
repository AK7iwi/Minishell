/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:02:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/13 18:00:55 by mfeldman         ###   ########.fr       */
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
		if (check_operator(current))
		{
			printf("Check operator\n");
			return (data->err.parsing_errors |= ERR_OPERATOR, EXIT_FAILURE);
		}
		else if (check_paren(current, &o_count, &c_count))
		{
			printf("Check paren\n");
			return (data->err.parsing_errors |= ERR_PARAN, EXIT_FAILURE);
		}
		else if (check_redir(current))
		{
			printf("Check redir\n");
			return (data->err.parsing_errors |= ERR_REDIR, EXIT_FAILURE);
		}
		current = current->next;
    }
	
	if (o_count != c_count) //replace by if o_counter - c_counter > 1
		return (data->err.parsing_errors |= ERR_PARAN, EXIT_FAILURE);
	
    return (EXIT_SUCCESS);
}


