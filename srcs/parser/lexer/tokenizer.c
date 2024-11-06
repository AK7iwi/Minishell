/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/06 10:44:29 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tokenizer(t_data *data, char *input)
{
	size_t 		input_len;
	size_t		i;
	
	input_len = ft_strlen(input);
	if (input_len <= 0)
		return (EXIT_FAILURE);
	
	i = 0;
	while (i < input_len)
	{	
		if (str_handler(data, input, &i)) //handle_str
			return (EXIT_FAILURE);
		if (special_char_handler(data, input, &i)) // handle_special_char
			return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}