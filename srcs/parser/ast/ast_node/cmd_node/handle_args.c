/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:16:14 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/23 12:22:49 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t get_args_len(t_token *current, size_t *i)
{
	size_t args_len;

	args_len = 0;
	
    while (current && is_cmd(current->type) && !is_redir(current->type))
    {
        args_len++;
		(*i)++;
        current = current->next;
    } 

	return (args_len);
}
static	char **copy_args(t_token **current, size_t *i)
{
	char **args;
	size_t args_len;
	size_t j;

	args_len = get_args_len((*current), i); //handle if args_len == 0
	if (args_len <= 0)
		return (NULL);  
	
	args = malloc((args_len + 1) * sizeof(char *));
	if (!args)
        return (NULL);
	
	j = 0;
	while (j < args_len) // && args_len
	{
		args[j++] = ft_strdup((*current)->str);
		(*current) = (*current)->next;
	}
	args[j] = NULL;
	
	return (args);
}
bool handle_args(t_ast **new_node, t_token **current, size_t *i)
{
	(*new_node)->cmd.args = copy_args(current, i);
	return ((*new_node)->cmd.args);
}