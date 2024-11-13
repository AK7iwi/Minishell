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

// Vérifie si le nom correspond au motif avec wildcards
static int is_match(char *name, char *pattern) 
{
    int i = 0;
    int j = 0;

    while (pattern[i] && name[j])
	 {
        if (pattern[i] == '*') 
		{
            i++;
            if (!pattern[i])
                return 1;
            while (name[j] && name[j] != pattern[i])
                j++;
        } 
		else if (pattern[i] == name[j]) 
		{
            i++;
            j++;
        } 
		else 
            return 0;
    }
    return (pattern[i] == '*' && !pattern[i + 1]) || (!pattern[i] && !name[j]);
}

// Ajoute un nouveau token en fin de liste chaînée
static void add_token_back(t_token **list, char *str) 
{
    t_token *new_token = malloc(sizeof(t_token));
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
        t_token *current = *list;
        while (current->next)
            current = current->next;
        current->next = new_token;
        new_token->prev = current;
    }
}

// Crée une liste de tokens correspondant au motif
static t_token *create_match_list(char *pattern) 
{
    DIR *dir = opendir(".");
    struct dirent *entry;
    t_token *match_list = NULL;

    if (!dir) 
	{
        perror("opendir");
        return NULL;
    }
    while ((entry = readdir(dir)) != NULL) 
	{
        if (entry->d_name[0] != '.' && is_match(entry->d_name, pattern)) 
            add_token_back(&match_list, ft_strdup(entry->d_name));
    }
    closedir(dir);
    return match_list;
}

// Fonction principale pour l'expansion des wildcards
void expand_from_wc(t_token **token) 
{
    t_token *match_list = create_match_list((*token)->str);
    if (!match_list)
        return;

    // Raccorde la liste match_list avec les tokens existants
    t_token *next = (*token)->next;
    t_token *prev = (*token)->prev;

    if (prev)
        prev->next = match_list;
    match_list->prev = prev;

    t_token *last = match_list;
    while (last->next)
        last = last->next;
    last->next = next;
    if (next)
        next->prev = last;

    // Libère le token original après l'expansion
    free((*token)->str);
    free(*token);
    *token = match_list;  // Remplace le token par la liste de correspondances
}

