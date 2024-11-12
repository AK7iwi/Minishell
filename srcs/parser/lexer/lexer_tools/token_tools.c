/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:14:17 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 09:54:16 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
