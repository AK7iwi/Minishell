/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:11:31 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_special_char(t_data *data, char *input, size_t *index)
{
	char 		*str_token;
	t_tok_type	token;
	
	str_token = extract_special_char(&data->err, input, index);
	if (!str_token)
		return (EXIT_FAILURE);
	
	token = wich_token(str_token);
	if (add_token(&data->tok, &token, str_token))
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
		
	return (EXIT_SUCCESS);
}