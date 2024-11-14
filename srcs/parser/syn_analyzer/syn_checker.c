/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:09:55 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/14 12:42:17 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_redir(t_err *err, t_tok *current)
{
	if (is_redir(current->type))
	{
		if (current->prev && is_redir(current->prev->type))
			return (EXIT_FAILURE);
		else if (!current->next 
				|| !is_word(current->next->type))
			return (EXIT_FAILURE);
	}
	(void)err;
	return (EXIT_SUCCESS);
}

bool	check_operator(t_err *err, t_tok *current)
{
	uint16_t err;

	err = 

	if (is_operator(current->type))
	{
		if (!current->prev || !current->next)
			return (EXIT_FAILURE);
		else if (!is_word(current->prev->type) 
				&& !is_closed_paren(current->prev->type))
			return (EXIT_FAILURE);
		else if (!is_word(current->next->type)
				&& !is_open_paren(current->next->type)
				&& !is_redir(current->next->type))
			return (EXIT_FAILURE);
	}
	(void)err;
	
	return (EXIT_SUCCESS);
}

bool	check_paren(t_err *err, t_tok *current, uint32_t *o, uint32_t *c)
{
	if (is_open_paren(current->type))
	{
		if (current->prev && !is_operator(current->prev->type))
			return (err->parsing_errors |= ERR_O_PAREN, EXIT_FAILURE);
		else if (!current->next 
				|| (!is_word(current->next->type)
					&& !is_redir(current->next->type)))
			return (err->parsing_errors |= ERR_O_PAREN, EXIT_FAILURE);
		(*o)++;
	}
	else if (is_closed_paren(current->type))
	{
		if (!current->prev || !is_word(current->prev->type))
			return (err->parsing_errors |= ERR_C_PAREN, EXIT_FAILURE);
		else if (current->next 
				&& !is_operator(current->next->type)
				&& !is_redir(current->next->type))
			return (err->parsing_errors |= ERR_C_PAREN, EXIT_FAILURE);
		(*c)++;
	}
	return ((*c) > (*o)); // display_error 
}