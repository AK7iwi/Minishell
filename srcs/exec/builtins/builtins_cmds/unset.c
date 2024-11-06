/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:45:10 by diguler           #+#    #+#             */
/*   Updated: 2024/11/06 14:44:13 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool unset(t_data *data, char **args)
{
    size_t i;
	
	if (!args[1])
        return (data->error.exec_errors |= ERR_UNSET, EXIT_FAILURE);
	
	i = 1;
	while (args[i])
    {
        unset_env_var(&data->env, args[i]);
        i++;
    }

	return (EXIT_SUCCESS);
}

