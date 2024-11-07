/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 12:26:07 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_str(t_data *data, char *input, size_t *i)
{
	t_tok_type	type;
	char		*str;
	
	type = T_WORD;
	str = extract_str(&data->err, input, &type, i);
	if (!str)
		return (EXIT_FAILURE);
	if (add_token(&data->tok, &type, str))
	{
		free(str);
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	}
	free(str);
	return (EXIT_SUCCESS);
}