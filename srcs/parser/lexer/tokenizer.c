/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/27 17:39:01 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tokenizer(t_data *data, char *input)
{
	t_tok_type	token; //delcare in str_handler and special_char_handler
	size_t 		input_len;
	size_t		i;
	
	input_len = ft_strlen(input);
	if (input_len <= 0)
		return (EXIT_SUCCESS);
	
	i = 0;
	while (i < input_len)
	{	
		token = 0;
		if (str_handler(data, input, &token, &i)) //handle_str
			return (EXIT_FAILURE);
		if (special_char_handler(data, input, &token, &i)) // handle_special_char
			return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}