/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:16:14 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:08:18 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t get_args_len(t_tok *current, size_t *i)
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
static	char **copy_args(t_ast **new_node, t_tok **current, size_t *i)
{
	char **args;
	size_t j;

	(*new_node)->cmd.args_count = get_args_len((*current), i);
	args = malloc(((*new_node)->cmd.args_count + 1) * sizeof(char *));
	if (!args)
        return (NULL);
	
	j = 0;
	while (j < (*new_node)->cmd.args_count)
	{
		args[j++] = ft_strdup((*current)->str);
		(*current) = (*current)->next;
	}
	args[j] = NULL;
	
	return (args);
}
bool	parse_args(t_ast **new_node, t_tok **current, size_t *i)
{
	char **args;

	args = copy_args(new_node, current, i);
	if (!args)
		return (EXIT_FAILURE);
	
	if ((*new_node)->cmd.args_count)
		(*new_node)->cmd.args = args;
	else
		free(args);
	
	return (EXIT_SUCCESS);
}