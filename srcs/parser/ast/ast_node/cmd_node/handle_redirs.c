/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:16:25 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/24 14:50:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t get_redirs_len(t_token *current, size_t *i)
{
	size_t redirs_len;
	//int 2word_in_a_row;

	redirs_len = 0;
	
    while (current && is_cmd(current->type)) //cond for cmd 2 words in a row
    {
        redirs_len++;
		(*i)++;
        current = current->next;
    }
	
	return (redirs_len);
}

static	char ** copy_redirs(t_token **current, size_t *i)
{
	char **redirs;
	size_t redirs_len;
	size_t j;

	redirs_len = get_redirs_len((*current), i);
	if (redirs_len < 0)
		return (NULL); 
	
	redirs = malloc((redirs_len + 1) * sizeof(char *));
	if (!redirs)
        return (NULL);
	
	j = 0;
	//test print if no redir
	while (j < redirs_len)
	{
		redirs[j++] = ft_strdup((*current)->str);
		//cpy_outfile, infile, delim 
		(*current) = (*current)->next;
	}
	redirs[j] = NULL;
	
	return (redirs);
}

bool handle_redirs(t_ast **new_node, t_token **current, size_t *i)
{
	(*new_node)->cmd.redirs = copy_redirs(current, i);
	return ((*new_node)->cmd.redirs);
}