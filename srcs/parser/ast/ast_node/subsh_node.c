/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:24:08 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/18 02:18:43 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_subsh_node(t_ast **new_node, t_tok **current)
{
	(*new_node)->type = AST_SUBSH;
	(*current) = (*current)->next;
	if (ast_algo(&(*new_node)->subshell.root, current, 0))
		return (EXIT_FAILURE);
	while (!is_c_paren((*current)->type))
		(*current) = (*current)->next;
	(*current) = (*current)->next;
	
	return (EXIT_SUCCESS);
}