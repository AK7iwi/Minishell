/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extracter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:21:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 14:40:36 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	handle_quotes(char *input, char *str, size_t *start, size_t *i, bool *need_expand)
{
	char	quote_char;

	quote_char = '\0';
	if (input[*start] == '\"')
	{
		*need_expand = true;
		quote_char = input[*start];
		(*start)++;
		while (input[*start] != quote_char && input[*start] != NULL_CHAR)
			str[(*i)++] = input[(*start)++];
		return (true);
	}
	else if (input[*start] == '\'')
	{
		*need_expand = false;
		quote_char = input[*start];
		(*start)++;
		while (input[*start] != quote_char && input[*start] != NULL_CHAR)
			str[(*i)++] = input[(*start)++];
		return (true);
	}
	return (false);
}

static char* copy_str(char *input, size_t start, size_t *end, size_t len, bool *need_expand)
{
	char *str;
	size_t i;
	
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	
	i = 0;
	while (start < (*end))
	{
		if (handle_quotes(input, str, &start, &i, need_expand))
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

char*	str_extracter(t_error *error, char *input, t_tok_type *token, size_t *index, bool *need_expand)
{
	size_t 	str_start;
	ssize_t	str_len;
	char*	str;
	
	str_start = skip_space(input, index);
	str_len = get_str_len(input, token, index); //in copy_str
	if (str_len < 0)
		return (error->parsing_errors |= ERROR_QUOTE, NULL);
	
	str = copy_str(input, str_start, index, str_len, need_expand);
	if (!str)
		return (error->gen_errors |= ERROR_MALLOC, NULL);

	return (str);
}
