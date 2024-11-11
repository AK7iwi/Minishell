/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:21:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/11 18:52:31 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	handle_quotes(char *input, char *str, size_t *start, size_t *i)
{
	char	quote_char;

	quote_char = '\0';
	if ((input[*start] == '\'' || input[*start] == '\"'))
    {
		quote_char = input[*start];
       	(*start)++;
        while (input[*start] != quote_char && input[*start] != '\0')
			str[(*i)++] = input[(*start)++];
		return (true);
    }
	return (false);
}

static char	*copy_str(char *input, size_t start, size_t *end, size_t len)
{
	char *str;
	size_t i;
	
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	
	i = 0;
	while (start < (*end))
	{
		if (handle_quotes(input, str, &start, &i))
			start++;
		else 
			str[i++] = input[start++];	
	}
	str[i] = '\0';
	return (str);
}
char	*extract_str(t_err *err, char *input, t_tok_type *type, size_t *i)
{
	size_t 	start;
	ssize_t	len;
	char	*str;
	
	start = (*i);
	len = get_str_len(input, type, i);
	if (len < 0)
		return (err->parsing_errors |= ERR_QUOTE, NULL);
	
	str = copy_str(input, start, i, len);
	if (!str)
		return (err->gen_errors |= ERR_MALLOC, NULL);
	
	return (str);
}
