/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/10 00:56:06 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void add_to_token_list(t_token **tokens, uint8_t input_type, char *str) 
{
    t_token *new_node;
    t_token *last;

    new_node = (t_token *)malloc(sizeof(t_token));
    if (!new_node)
        return ;

    new_node->type = input_type;
    new_node->str = ft_strdup(str);
    new_node->next = NULL;

    if (*tokens == NULL) 
    {
        new_node->prev = NULL;
        *tokens = new_node;  
        return ;
    }
    last = *tokens;
    while (last->next)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;
}

uint8_t wich_token(char *input)
{
    if (input[0] == '|' && !input[1])
        return (TOKEN_PIPE);
    else if (input[0] == '<' && !input[1])
        return (TOKEN_SIMPLE_REDIRECT_IN);
    else if (input[0] == '>' && !input[1])
        return (TOKEN_SIMPLE_REDIRECT_OUT);
    else if (input[0] == '<' && input[1] == '<' && !input[2])
        return (TOKEN_DOUBLE_REDIRECT_IN);
    else if (input[0] == '>' && input[1] == '>' && !input[2])
        return (TOKEN_DOUBLE_REDIRECT_OUT);
    else if (input[0] == '&' && !input[1])
        return (TOKEN_ENV_VARIABLE);
    else if (input[0] == '&' && input[1] == '&' && !input[2])
        return (TOKEN_AND);
    else if (input[0] == '|' && input[1] == '|' && !input[2])
        return (TOKEN_OR);
    else if (input[0] == '(' && !input[1])
        return (TOKEN_OPEN_PAREN);
    else if (input[0] == ')' && !input[1])
        return (TOKEN_CLOSE_PAREN);
   
    return (TOKEN_WORD);
}

static char*	extract_str(char *input, size_t start, size_t end, size_t str_len)
{
	size_t i;
	char *str;
	char quote_char;
	bool open_quote;
	
	str = (char *)malloc((str_len) + 1);
	if (!str)
		return (NULL);
		
	i = 0;
	quote_char = '\0';
	open_quote = false;
	
	while (start < end)
	{
		if ((input[start] == '\'' || input[start] == '\"') && !open_quote) 
        {
			open_quote = true;
            quote_char = input[start];
            start++;
            while (input[start] != quote_char && input[start] != '\0')
			{
				str[i++] = input[start];
                start++;
			}
            if (input[start] == quote_char)
				open_quote = false;
        }
		else 
			str[i++] = input[start];
		start++;	
	}
	
	str[i] = '\0';
	
	return (str);
}

static size_t skip_quotes_until_find_next_space_or_end(char *input, size_t *i)
{
    size_t len;
    char quote_char;
	bool open_quote;

	len = 0;
	quote_char = '\0';
	open_quote = false;
	
    while (input[*i] != ' ' && input[*i] != '\0')
    {
        if ((input[*i] == '\'' || input[*i] == '\"') && !open_quote) 
        {
			open_quote = true;
            quote_char = input[*i];
            (*i)++;
            while (input[*i] != quote_char && input[*i] != '\0')
            {
                len++;
                (*i)++;
            }
            if (input[*i] == quote_char)
				open_quote = false;
			else if (input[*i] == '\0')
				return (-1);		
        }
        else
            len++;
		
		(*i)++;
    }
	
    return (len);
}

static size_t skip_space(char *input, size_t *i)
{
	while (input[*i] == ' ')
		(*i)++;

	return (*i);
}		

bool	tokenisation(char *input, t_token **tokens)
{
	char 		*str;
	uint8_t		token;
	size_t		str_start;
	int64_t		str_len;
	size_t		str_end;
	size_t		i;
	
	i = 0;
	while (input[i])
	{
		str_start = skip_space(input, &i);
		str_len = skip_quotes_until_find_next_space_or_end(input, &i);
		if (str_len == -1)
			return (EXIT_FAILURE);	//error open_quotes	
		str_end = i;
		str = extract_str(input, str_start, str_end, str_len);
		if (!str)
			return (EXIT_FAILURE);	
		token = wich_token(str);
		add_to_token_list(tokens, token, str);
		free(str);
        i++;
	}
	
	return (EXIT_SUCCESS);
}
