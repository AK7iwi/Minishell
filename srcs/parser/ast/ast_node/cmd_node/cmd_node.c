/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:29:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/24 18:21:57 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t get_cmd_len(t_token *current)
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

t_ast	*create_cmd_node(t_ast **new_node, t_token **current)
{	
	size_t cmd_len;
	size_t i;
	
	cmd_len = get_cmd_len((*current));

	(*new_node)->type = AST_COMMAND;
	(*new_node)->cmd.args = NULL; //check if need
	(*new_node)->cmd.redirs = NULL;
	(*new_node)->cmd.f_args = false;
	(*new_node)->cmd.f_redirs = false;
	
	// (*new_node)->cmd.redirs_files->input_file = NULL;
	// (*new_node)->cmd.redirs_files->output_file = NULL;
	// (*new_node)->cmd.redirs_files->delim = NULL;
	i = 0;
	while (i < cmd_len)
	{
		if (!handle_args(new_node, current, &i))
			return (NULL);
		if (!handle_redirs(new_node, current, &i))
			return (NULL);
	}
	
	return ((*new_node));
}