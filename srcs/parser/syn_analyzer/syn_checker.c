/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:09:55 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/13 18:18:21 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_redir(t_tok *current)
{
	if (is_redir(current->type))
	{
		printf("is_redir\n");
		if (current->prev && is_redir(current->prev->type))
		{
			printf("prev\n");
			return (EXIT_FAILURE);
		}
		else if (!current->next 
				|| (current->next->type != T_WORD 
					&& current->next->type != T_ENV_VAR))
		{
			printf("next\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
bool	check_paren(t_tok *current, uint32_t *o_count, uint32_t *c_count)
{
	if (is_open_paren(current->type))
	{
		printf("is_open_paren\n");
		if (current->prev && !is_operator(current->prev->type))
		{
			printf("prev\n");
			return (EXIT_FAILURE);
		}
		else if (!current->next 
				|| (current->next->type != T_WORD
					&& current->next->type != T_ENV_VAR
					&& !is_redir(current->next->type)))
		{
			printf("next\n");
			return (EXIT_FAILURE);
		}
		(*o_count)++;
	}
	else if (is_closed_paren(current->type))
	{
		printf("is_closed_paren\n");
		if (!current->prev
			|| (current->prev->type != T_WORD
			&& current->prev->type != T_ENV_VAR))
		{
			printf("prev\n");
			return (EXIT_FAILURE);
		}
		else if (current->next 
				&& !is_operator(current->next->type)
				&& !is_redir(current->next->type))
		{
			printf("next\n");
			return (EXIT_FAILURE);
		}
		(*c_count)++;
	}
	return ((*c_count) > (*o_count));
}

bool	check_operator(t_tok *current)
{
	if (is_operator(current->type))
	{
		printf("is_operator\n");
		if (!current->prev || !current->next)
		{
			printf("R\n");
			return (EXIT_FAILURE);
		}
		else if (current->prev->type != T_WORD 
				&& current->prev->type != T_ENV_VAR
				&& current->prev->type != T_C_PAREN) //is_closed_paren
		{
			printf("prev\n");
			return (EXIT_FAILURE);
		}
		else if (current->next->type != T_WORD
				&& current->next->type != T_ENV_VAR
				&& current->next->type != T_O_PAREN //is_open_paren
				&& !is_redir(current->next->type))
		{
			printf("next\n");
			return (EXIT_FAILURE);
		}
	}
	
	return (EXIT_SUCCESS);
}