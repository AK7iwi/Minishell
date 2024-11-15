/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:09:55 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/15 12:27:05 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	uint16_t	get_type_error(t_tok_type type)
{
	uint16_t err;
	err = 0;

	if (is_pipe(type))
		err = ERR_PIPE;
	else if (is_and(type))
		err = ERR_AND; 
	else if (is_or(type))
		err = ERR_OR;
	else if (is_s_redir_out(type))
		err = ERR_S_REDIR_OUT;
	else if (is_d_redir_out(type))
		err = ERR_D_REDIR_OUT;
	else if (is_redir_in(type))
		err = ERR_REDIR_IN;
	else if (is_heredoc(type))
		err = ERR_HEREDOC;
	return (err);
}

bool	check_redir(t_err *err, t_tok *current)
{
	uint16_t error;

	error = get_type_error(current->type);
	
	if (is_redir(current->type))
	{
		if (current->prev && is_redir(current->prev->type))
			return (err->parsing_errors |= error, EXIT_FAILURE);
		else if (!current->next
				|| !is_word(current->next->type))
			return (err->parsing_errors |= error, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	check_operator(t_err *err, t_tok *current)
{
	uint16_t error;

	error = get_type_error(current->type);

	if (is_operator(current->type))
	{
		if (!current->prev || !current->next)
			return (err->parsing_errors |= error, EXIT_FAILURE);
		else if (!is_word(current->prev->type) 
				&& !is_closed_paren(current->prev->type))
			return (err->parsing_errors |= error, EXIT_FAILURE);
		else if (!is_word(current->next->type)
				&& !is_open_paren(current->next->type)
				&& !is_redir(current->next->type))
			return (err->parsing_errors |= error, EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}

bool	check_paren(t_err *err, t_tok *current, uint32_t *o, uint32_t *c)
{
	//two fct 
	if (is_open_paren(current->type))
	{
		if (current->prev 
			&& !is_operator(current->prev->type)
			&& !is_open_paren(current->prev->type))
			return (err->parsing_errors |= ERR_O_PAREN, EXIT_FAILURE);
		else if (!current->next
				|| (!is_word(current->next->type)
				&& !is_redir(current->next->type)
				&& !is_open_paren(current->next->type)))
			return (err->parsing_errors |= ERR_O_PAREN, EXIT_FAILURE);
		(*o)++;
	}
	else if (is_closed_paren(current->type))
	{
		if (!current->prev
			|| (!is_word(current->prev->type) 
			&& !is_closed_paren(current->prev->type)))
			return (err->parsing_errors |= ERR_C_PAREN, EXIT_FAILURE);
		else if (current->next 
				&& !is_operator(current->next->type)
				&& !is_redir(current->next->type)
				&& !is_closed_paren(current->next->type))
			return (err->parsing_errors |= ERR_C_PAREN, EXIT_FAILURE);
		(*c)++;
	}
	
	if ((*c) > (*o))
		return (err->parsing_errors |= ERR_C_PAREN, EXIT_FAILURE);
	 
	return (EXIT_SUCCESS);
}