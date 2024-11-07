/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:11:31 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_str(t_data *data, char *input, size_t *index)
{
	char		*str_token;
	t_tok_type	token;

	token = T_WORD;
	str_token = extract_str(&data->err, input, &token, index);
	if (!str_token)
	{
		printf("str_token\n");
		return (EXIT_FAILURE);
	}
	if (add_token(&data->tok, &token, str_token))
	{
		printf("add_token\n");
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}