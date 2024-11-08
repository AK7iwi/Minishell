/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:54:13 by diguler           #+#    #+#             */
/*   Updated: 2024/11/05 10:54:33 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Appeler expand_from_wc pour chaque token contenant un wildcard afin d'expanser les motifs dans la commande

// Vérifie si le nom correspond au motif avec wildcards
static int	is_match(char *name, char *pattern)
{
	int		i;
	int		j;
	int		star_index;
	char	*sub;

	i = 0;
	j = 0;
	if (pattern[0] != '*' && pattern[0] != name[0])
		return (0);
	while (pattern[i])
	{
		while (pattern[i] == '*')
			i++;
		if (!pattern[i])
			return (1);
		
		// Trouver la longueur de la sous-chaîne jusqu'au prochain '*'
		star_index = 0;
		while (pattern[i + star_index] && pattern[i + star_index] != '*')
			star_index++;
		
		sub = ft_substr(pattern + i, 0, star_index);
		if (!sub)
			return (0);
		
		j += index_n(name + j, sub, 1);
		free(sub);
		if (!name[j])
			return (0);
		
		i += star_index;
	}
	return (1);
}


// Ajoute un nouveau token en fin de liste chaînée
static void	add_token_back(t_token **list, char *str)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return;
	new_token->str = str;
	new_token->type = T_WORD;
	new_token->next = NULL;
	new_token->prev = NULL;

	if (!*list)
		*list = new_token;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
}

// Crée une liste de tokens correspondant au motif
static t_token	*create_match_list(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*match_list = NULL;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return (NULL);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.' && is_match(entry->d_name, pattern))
			add_token_back(&match_list, ft_strdup(entry->d_name));
	}
	closedir(dir);
	return (match_list);
}

// Fonction principale pour l'expansion des wildcards
void	expand_from_wc(t_token **token)
{
	t_token	*match_list;
	t_token	*next;
	t_token	*prev;

	// Crée la liste de correspondances pour le token actuel
	match_list = create_match_list((*token)->str);
	if (!match_list)
		return ;
	
	next = (*token)->next;
	prev = (*token)->prev;

	// Connecte le token précédent à la liste de correspondances
	if (prev)
		prev->next = match_list;
	match_list->prev = prev;

	// Connecte le dernier token de la liste avec le suivant
	t_token *last = match_list;
	while (last->next)
		last = last->next;
	last->next = next;
	if (next)
		next->prev = last;

	// Libère le token original après l'expansion
	free((*token)->str);
	free(*token);
	*token = prev ? prev : match_list;
}