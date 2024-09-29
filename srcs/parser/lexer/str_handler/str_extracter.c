/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extracter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:21:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/27 12:03:47 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	quotes_handler(char *input, char *str, size_t *start, size_t *i)
{
	char	quote_char;

	quote_char = '\0';
	if ((input[*start] == '\'' || input[*start] == '\"'))
    {
		quote_char = input[*start];
       	(*start)++;
        while (input[*start] != quote_char && input[*start] != NULL_CHAR)
			str[(*i)++] = input[(*start)++];
		return (true);
    }
	
	return (false);
}

static char* copy_str(char *input, size_t start, size_t *end, size_t len)
{
	char *str;
	size_t i;
	
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	
	i = 0;
	while (start < (*end))
	{
		if (quotes_handler(input, str, &start, &i))
			start++;
		else 
			str[i++] = input[start++];	
	}
	
	str[i] = '\0';
	
	return (str);
}

static size_t skip_space(char *input, size_t *i)
{
	while (input[*i] == SPACE)
		(*i)++;

	return (*i);
}

char*	str_extracter(t_error *error, char *input, t_tok_type *token, size_t *index)
{
	size_t 	str_start;
	ssize_t	str_len;
	char*	str;
	
	str_start = skip_space(input, index);
	str_len = get_str_len(input, token, index);
	if (str_len < 0)
		return (error->error_g |= ERROR_QUOTE, NULL);
	
	str = copy_str(input, str_start, index, str_len);
	if (!str)
		return (error->error_g |= ERROR_MALLOC, NULL);

	return (str);
}