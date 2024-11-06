/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:16:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/06 16:26:20 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_env(t_data *data, char **envp)
{
	size_t	i;

	if (!*envp)
		return (create_env(data));

	i = 0;
	while (envp[i])
	{
		if (add_env_var(&data->env, envp[i]))
			return (data->error.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
