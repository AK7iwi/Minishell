/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 14:21:22 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parser tools
bool	is_special_char(char *input, size_t *i)
{
	return (input[*i] == '|' 
			|| input[*i] == '<' 
			|| input[*i] == '>' 
			|| input[*i] == '&' 
			|| input[*i] == '(' 
			|| input[*i] == ')');
}
bool	special_char_handler(t_data *data, char *input, t_tok_type *token, size_t *index, bool need_expand)
{
	char *str_token;
	
	str_token = special_char_extracter(&data->error, input, index);
	if (!str_token)
		return (EXIT_FAILURE);
	
	(*token) = wich_token(str_token);
	if (add_token(&data->token, token, str_token, need_expand))
		return (data->error.gen_errors |= ERROR_MALLOC, EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}