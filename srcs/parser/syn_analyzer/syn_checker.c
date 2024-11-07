/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:09:55 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:08:18 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_paren(t_tok *current, uint32_t *o_counter, uint32_t *c_counter)
{
	if (is_open_paren(current->type))
		(*o_counter)++;
	else if (is_closed_paren(current->type))
		(*c_counter)++;
	
	return ((*c_counter) > (*o_counter));
}
bool check_redir(t_tok *current)
{
	return (is_redir(current->type)
		&& (!current->next || current->next->type != T_WORD));
	
}
bool check_operator(t_tok *current)
{	
	return (is_operator(current->type)
			&& ((!current->prev || (current->prev->type != T_WORD && current->prev->type != T_C_PAREN  && current->prev->type != T_ENV_VAR))
			|| (!current->next || (current->next->type != T_WORD && current->next->type != T_O_PAREN))));
}