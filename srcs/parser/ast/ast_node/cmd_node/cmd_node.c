/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:29:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:08:18 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t get_cmd_len(t_tok *current)
{
	size_t cmd_len;

	cmd_len = 0;
	
    while (current && !is_operator(current->type))
    {
        cmd_len++;
        current = current->next;
    } 

	return (cmd_len);
}

t_ast	*create_cmd_node(t_ast **new_node, t_tok **current)
{	
	size_t cmd_len;
	size_t i;
	
	cmd_len = get_cmd_len((*current));
	(*new_node)->type = AST_COMMAND;
	(*new_node)->cmd.args = NULL;
	(*new_node)->cmd.redirs = NULL;
	(*new_node)->cmd.redir = NULL;
	i = 0;
	while (i < cmd_len)
	{
		if (parse_args(new_node, current, &i))
			return (NULL);
		if (parse_redirs(new_node, current, &i))
			return (NULL);
	}
	
	return ((*new_node));
}