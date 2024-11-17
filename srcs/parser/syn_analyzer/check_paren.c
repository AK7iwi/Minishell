/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paren.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:26:10 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/17 15:15:15 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	check_c_paren(t_tok *current, uint32_t *c)
{
	if (is_c_paren(current->type))
	{
		if (!current->prev
			|| (!is_word(current->prev->type)
				&& !is_c_paren(current->prev->type)))
			return (EXIT_FAILURE);
		else if (current->next
			&& !is_operator(current->next->type)
			&& !is_redir(current->next->type)
			&& !is_c_paren(current->next->type))
			return (EXIT_FAILURE);
		(*c)++;
	}
	return (EXIT_SUCCESS);
}

static	bool	check_o_paren(t_tok *current, uint32_t *o)
{
	if (is_o_paren(current->type))
	{
		if (current->prev
			&& !is_operator(current->prev->type)
			&& !is_o_paren(current->prev->type))
			return (EXIT_FAILURE);
		else if (!current->next
			|| (!is_word(current->next->type)
				&& !is_redir(current->next->type)
				&& !is_o_paren(current->next->type)))
			return (EXIT_FAILURE);
		(*o)++;
	}
	return (EXIT_SUCCESS);
}

bool	check_paren(t_err *err, t_tok *current, uint32_t *o, uint32_t *c)
{
	if (check_o_paren(current, o))
		return (err->parsing_errors |= ERR_O_PAREN, EXIT_FAILURE);
	else if (check_c_paren(current, c) || (*c) > (*o))
		return (err->parsing_errors |= ERR_C_PAREN, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
