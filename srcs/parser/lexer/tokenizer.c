/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 08:21:13 by mfeldman         ###   ########.fr       */
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
		if (handle_str(data, input, &i))
		{
			printf("Je passe str\n");
			return (EXIT_FAILURE);
		}
		if (handle_special_char(data, input, &i))
		{
			printf("Je passe special char\n");
			return (EXIT_FAILURE);
		}
	}
	
	return (EXIT_SUCCESS);
}