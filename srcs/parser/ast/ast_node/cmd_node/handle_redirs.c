/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:16:25 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/26 12:52:18 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t get_redirs_len(t_token *current, size_t *i)
{
	size_t redirs_len;
	bool	word_in_a_row;
	
	redirs_len = 0;
	word_in_a_row = false; //review this logic 
	
    while (current && is_cmd(current->type))
    {
		if (is_redir(current->type))
			word_in_a_row = 0;
		else
		{
			if (word_in_a_row)
			{
				(*i)++;		
				return (redirs_len);
			}
			word_in_a_row = true;
		}
        redirs_len++;
		(*i)++;
        current = current->next;
    }
	
	return (redirs_len);
}

static	char ** copy_redirs(t_ast **new_node, t_token **current, size_t *i)
{
	char **redirs;
	size_t redirs_len;
	size_t j;

	redirs_len = get_redirs_len((*current), i);
	if (redirs_len < 0)
		return (NULL); 
	(*new_node)->cmd.redirs_count = redirs_len;
	redirs = malloc((redirs_len + 1) * sizeof(char *));
	if (!redirs)
        return (NULL);
	
	j = 0;
	//test print if no redir
	while (j < redirs_len)
	{
		redirs[j++] = ft_strdup((*current)->str);
		//cpy and free outfile, infile, delim 
		(*current) = (*current)->next;
	}
	redirs[j] = NULL;
	
	return (redirs);
}
bool handle_redirs(t_ast **new_node, t_token **current, size_t *i)
{
	char **redirs;

	redirs = copy_redirs(new_node, current, i);
	if (!redirs)
		return (EXIT_FAILURE);
	
	
	if ((*new_node)->cmd.redirs_count) //test if need 
		(*new_node)->cmd.redirs = redirs;
	else 
		free(redirs); //test to see when pass
	
	return (EXIT_SUCCESS);
}