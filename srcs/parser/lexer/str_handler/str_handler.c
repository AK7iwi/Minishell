/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/23 10:50:03 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool str_handler(t_data *data, char *input, t_tok_type *token, size_t *index)
{
	char	*str_token;

	str_token = str_extracter(&data->error, input, token, index); //extract_str
	if (!str_token)
		return (EXIT_FAILURE);
	if (!(*token))
		(*token) = T_WORD;
	if (add_token(&data->token, token, str_token))
		return (data->error.gen_errors |= ERROR_MALLOC, EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}