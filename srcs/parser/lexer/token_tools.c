/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:14:17 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/09 12:30:20 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_special_char(char *input, size_t *i)
{
	return (input[*i] == '|' 
			|| input[*i] == '<' 
			|| input[*i] == '>' 
			|| input[*i] == '&' 
			|| input[*i] == '(' 
			|| input[*i] == ')');
}

void	free_token(t_tok **tokens) //free folder
{
	t_tok	*tmp;
	t_tok	*current;

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

static	bool add_to_tok_list(t_tok **tok, t_tok_type *type, char *str) 
{
    t_tok *new_token;
    t_tok *last;

    new_token = malloc(sizeof(t_tok));
    if (!new_token)
        return (EXIT_FAILURE);

    new_token->type = (*type);
    new_token->str = ft_strdup(str);
	if (!new_token->str)
		return (free(new_token), EXIT_FAILURE);
    new_token->next = NULL;

    if (*tok == NULL) 
    {
        new_token->prev = NULL;
        *tok = new_token;  
        return (EXIT_SUCCESS);
    }
    last = *tok;
    while (last->next)
        last = last->next;
    last->next = new_token;
    new_token->prev = last;
	return (EXIT_SUCCESS);
}

bool	add_token(t_tok **tok, t_tok_type *type, char *str)
{
	return (ft_strlen(str) && add_to_tok_list(tok, type, str));
}
t_tok_type	wich_token(char *str_token) //wich type
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