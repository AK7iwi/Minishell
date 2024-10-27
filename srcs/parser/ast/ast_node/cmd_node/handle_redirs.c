/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:16:25 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/27 17:13:07 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	fill_file(t_redir **redir, char *file, uint8_t w_redir)
{
	char *cpy_file;

	cpy_file = ft_strdup(file);
	if (!cpy_file)
		return (EXIT_FAILURE);
	
	if (w_redir == 0)
	{
		if ((*redir)->i_file)
			free((*redir)->i_file);
		(*redir)->i_file = cpy_file;
	}
	else if (w_redir == 1)
	{
		if ((*redir)->o_file)
			free((*redir)->o_file);
		(*redir)->o_file = cpy_file;
	}
	else if (w_redir == 2)
	{
		if ((*redir)->delim)
			free((*redir)->delim);
		(*redir)->delim = cpy_file;
	}
	return (free(cpy_file), EXIT_SUCCESS);
}
static t_redir	*fill_redir_struct(char **redirs)
{
	t_redir *redir;
	size_t i;
	bool fill_check;
	
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);

	i = 0;
	fill_check = false;
	while (redirs[i])
	{
		if (ft_strncmp(redirs[i], "<", 2) == 0)
			fill_check = fill_file(&redir, redirs[i + 1], 0);
		else if (ft_strncmp(redirs[i], ">", 2) == 0 
			|| ft_strncmp(redirs[i], ">>", 3) == 0)
			fill_check = fill_file(&redir, redirs[i + 1], 1);	
		else if (ft_strncmp(redirs[i], "<<", 3) == 0)
			fill_check = fill_file(&redir, redirs[i + 1], 2);
		i++;
		if (fill_check)
			return (NULL);
	}
	
	return (redir);
}
static size_t get_redirs_len(t_token *current, size_t *i)
{
	size_t	redirs_len;
	bool	word_in_a_row;
	
	redirs_len = 0;
	word_in_a_row = false;
	
    while (current && is_cmd(current->type))
    {
		if (is_redir(current->type))
			word_in_a_row = false;
		else
		{
			if (word_in_a_row)
				break ;
			word_in_a_row = true;	
		}
        redirs_len++;
		(*i)++;
        current = current->next;
    }
	
	return (redirs_len);
}
static char	**copy_redirs(t_ast **new_node, t_token **current, size_t *i)
{
	char	**redirs;
	size_t	j;

	(*new_node)->cmd.redirs_count = get_redirs_len((*current), i);
	redirs = malloc(((*new_node)->cmd.redirs_count + 1) * sizeof(char *));
	if (!redirs)
        return (NULL);
	
	j = 0;
	while (j < (*new_node)->cmd.redirs_count)
	{
		redirs[j++] = ft_strdup((*current)->str);
		(*current) = (*current)->next;
	}
	redirs[j] = NULL;
	
	return (redirs);
}
bool handle_redirs(t_ast **new_node, t_token **current, size_t *i)
{
	char 	**redirs;

	redirs = copy_redirs(new_node, current, i);
	if (!redirs)
		return (EXIT_FAILURE);
	
	if ((*new_node)->cmd.redirs_count)
	{
		(*new_node)->cmd.redirs = redirs;
		(*new_node)->cmd.redir = fill_redir_struct(redirs);
		if (!(*new_node)->cmd.redir)
			return (EXIT_FAILURE);
	}
	else 
		free(redirs);
	
	return (EXIT_SUCCESS);
}