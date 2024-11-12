/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 14:36:54 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool str_handler(t_data *data, char *input, t_tok_type *token, size_t *index)
{
	char	*str_token;
	bool	need_expand = false;

	str_token = str_extracter(&data->error, input, token, index, &need_expand); //extract_str
	if (!str_token)
		return (EXIT_FAILURE);
	if (!(*token))
		(*token) = T_WORD;
	if (add_token(&data->token, token, str_token, need_expand))
		return (data->error.gen_errors |= ERROR_MALLOC, EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}
