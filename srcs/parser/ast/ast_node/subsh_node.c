/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:24:08 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/27 20:52:45 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_subsh_node(t_ast **new_node, t_token **current, t_env *env_list)
{
	(*new_node)->type = AST_SUBSH;
	(*current) = (*current)->next;
    (*new_node)->subshell.root = ast_algo(current, 0, env_list);
	while ((*current)->type != T_C_PAREN)
		(*current) = (*current)->next;
	(*current) = (*current)->next;
	
	return ((*new_node));
}