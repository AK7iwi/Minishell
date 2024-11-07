/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 12:38:52 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_special_char(t_data *data, char *input, size_t *index) //i
{
	t_tok_type	token; //type
	char 		*str_token; //str 
	
	str_token = extract_special_char(&data->err, input, index);
	if (!str_token)
		return (EXIT_FAILURE);
	
	token = wich_token(str_token);
	if (add_token(&data->tok, &token, str_token))
	{
		free(str_token);	
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	}
	
	free(str_token);
	return (EXIT_SUCCESS);
}