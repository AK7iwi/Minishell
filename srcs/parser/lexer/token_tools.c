/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:14:17 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 14:34:18 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token(t_token *token)
{
    t_token *current;
	
	current = token;
	
	printf("PRINT_TEST:\n");
    while (current)
    {
        printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
        current = current->next;
    }
}

void	free_token(t_token **tokens)
{
	t_token	*tmp;
	t_token	*current;

	if (!(*tokens))
		return ;
	current = *tokens;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
	}
	*tokens = NULL;
}

static	bool add_to_token_list(t_token **token, t_tok_type *str_type, char *str, bool need_expand) 
{
    t_token *new_node;
    t_token *last;

    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return (EXIT_FAILURE);

    new_node->type = (*str_type);
    new_node->str = ft_strdup(str);
    new_node->need_expand = need_expand; 
    
    if (!(new_node->str))
		return (EXIT_FAILURE);
    new_node->next = NULL;

    if (*token == NULL) 
    {
        new_node->prev = NULL;
        *token = new_node;  
        return (EXIT_SUCCESS);
    }
    last = *token;
    while (last->next)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;

	return (EXIT_SUCCESS);
}

bool	add_token(t_token **token_struct, t_tok_type *token, char *str_token, bool need_expand)
{
	if (ft_strlen(str_token))
		if (add_to_token_list(token_struct, token, str_token, need_expand))
			return (EXIT_FAILURE);
	free(str_token);
	return (EXIT_SUCCESS);
}

t_tok_type wich_token(char *str_token)
{
    if (str_token[0] == '|' && !str_token[1])
        return (T_PIPE);
    else if (str_token[0] == '<' && !str_token[1])
        return (T_S_REDIR_IN);
    else if (str_token[0] == '>' && !str_token[1])
        return (T_S_REDIR_OUT);
    else if (str_token[0] == '<' && str_token[1] == '<' && !str_token[2])
        return (T_HERE_DOC);
    else if (str_token[0] == '>' && str_token[1] == '>' && !str_token[2])
        return (T_D_REDIR_OUT);
    else if (str_token[0] == '&' && str_token[1] == '&' && !str_token[2])
        return (T_AND);
    else if (str_token[0] == '|' && str_token[1] == '|' && !str_token[2])
        return (T_OR);
    else if (str_token[0] == '(' && !str_token[1])
        return (T_O_PAREN);
    else if (str_token[0] == ')' && !str_token[1])
        return (T_C_PAREN);

    return (T_WORD);
}
