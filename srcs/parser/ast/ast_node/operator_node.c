/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:29:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/17 19:33:47 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_operator_node(t_ast *left, t_ast *right, t_op_type op_type)
{
	t_ast *new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	new_node->type = AST_OPERATOR;
	new_node->op.type = op_type;
	new_node->op.left = left;
	new_node->op.right = right;
	
	return (new_node);
}