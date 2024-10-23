/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:29:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/23 12:36:25 by mfeldman         ###   ########.fr       */
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
	printf("cmd_len:%li\n", cmd_len);

	(*new_node)->type = AST_COMMAND;
	(*new_node)->cmd.args = NULL; //check if need
	(*new_node)->cmd.redirs = NULL;
	
	(*new_node)->cmd.redirs_files->input_file = NULL;
	(*new_node)->cmd.redirs_files->output_file = NULL;
	(*new_node)->cmd.redirs_files->delim = NULL;
	i = 0;
	printf("oui\n");
	while (i < cmd_len)
	{
		printf("i:%li", i);
		if (!handle_args(new_node, current, &i))
			return (NULL);
		printf("i after args:%li", i);
		if (!handle_redirs(new_node, current, &i))
			return (NULL);
		// i++;
	}
	
	//test 
	return ((*new_node));
}