/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:29:48 by diguler           #+#    #+#             */
/*   Updated: 2024/10/18 10:03:29 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_exit(t_data *data, char **args)
{
	uint8_t exit_status;
	
	exit_status = 0;

	if (args[1])
	{
		if (!is_number(args[1]))
		{
			exit_status = 2;	
			printf("bash: exit: %s: numeric argument required\n", args[1]);
		}
		else if (args[2])
		{
			exit_status = 1;
			return (data->error.exec_errors |= ERROR_EXIT, exit_status);
		}
		else 
			exit_status = ft_atoi(args[1]);
	}
	
	free_all(data);
	exit(exit_status);
}