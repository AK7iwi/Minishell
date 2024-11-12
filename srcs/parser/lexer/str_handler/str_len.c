/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:20:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 09:41:44 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	get_quotes_len(char *inp, ssize_t *l, t_tok_type *t, size_t *i)
{
	char	quote_char;

	quote_char = '\0';
	if ((inp[*i] == '\'' || inp[*i] == '\"')) 
    {
        quote_char = inp[*i];
        (*i)++;
        while (inp[*i] != quote_char && inp[*i] != '\0')
        {
			if (inp[*i] == '$' && quote_char == '\"')
				(*t) = T_ENV_VAR;
			(*l)++;
            (*i)++;
        }
		(*l)--;
        if (inp[*i] != quote_char)
			return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}
ssize_t	get_str_len(char *input, t_tok_type *type, size_t *i)
{
    ssize_t	str_len;

	str_len = 0;
    while (!is_special_char(input, i) && input[*i] != ' ' && input[*i] != '\0')
    {
		if (input[*i] == '$')
			(*type) = T_ENV_VAR;
		if (get_quotes_len(input, &str_len, type, i))
			return (-1);
		else
        	str_len++;
		
		(*i)++;
	}
    return (str_len);
}
