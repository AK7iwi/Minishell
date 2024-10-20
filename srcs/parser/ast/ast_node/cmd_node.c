/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:29:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/20 19:39:00 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_redir(t_ast **new_node, t_token **current)
{
	while ((*current) && !is_operator((*current)->type))
	{
		if ((*current)->type == TOKEN_SIMPLE_REDIRECT_OUT || (*current)->type == TOKEN_DOUBLE_REDIRECT_OUT)
		{
			(*new_node)->cmd.output_file = ft_strdup((*current)->next->str);
			if ((*current)->type == TOKEN_DOUBLE_REDIRECT_OUT)
				(*new_node)->cmd.append = true;
		}
		else if ((*current)->type == TOKEN_SIMPLE_REDIRECT_IN)
			(*new_node)->cmd.input_file = ft_strdup((*current)->next->str);
		else if (((*current)->type) == TOKEN_HERE_DOC)
			(*new_node)->cmd.delim = ft_strdup((*current)->next->str);
		
		(*current) = (*current)->next;
		(*current) = (*current)->next;
	}
}
static char **copy_args(t_token **current, size_t cmd_len)
{
	char **args;
	size_t i;
	
	args = malloc((cmd_len + 1) * sizeof(char *));
	if (!args)
        return (NULL);
	i = 0;
	while (i < cmd_len)
	{
		args[i++] = ft_strdup((*current)->str);
		(*current) = (*current)->next;
	}
	args[i] = NULL;
	
	return (args);
}
static size_t get_cmd_len(t_token *current)
{
	size_t cmd_len;

	cmd_len = 0;
	
    while (current && is_cmd(current->type))
    {
        cmd_len++;
        current = current->next;
    } 

	return (cmd_len);
}
t_ast	*create_cmd_node(t_ast **new_node, t_token **current)
{
	size_t cmd_len;

	cmd_len = get_cmd_len((*current));
	if (cmd_len <= 0)
		return (NULL);
	
	(*new_node)->type = AST_COMMAND;
	(*new_node)->cmd.args = copy_args(current, cmd_len);
	if ((*current) && is_redir((*current)->type))
		handle_redir(new_node, current);
	
	return ((*new_node));
}