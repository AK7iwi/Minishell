/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:24:08 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/17 16:18:33 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_subsh_node(t_ast **new_node, t_tok **current)
{
	(*new_node)->type = AST_SUBSH;
	(*current) = (*current)->next;
    (*new_node)->subshell.root = ast_algo(current, 0);
	while ((*current)->type != T_C_PAREN)
		(*current) = (*current)->next;
	(*current) = (*current)->next;
	
	return ((*new_node));
}