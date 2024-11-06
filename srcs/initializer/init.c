/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:18:51 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/06 12:28:24 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void 	init_errors(t_data *data)
{
	data->error.gen_errors = 0;
	data->error.parsing_errors = 0;
	data->error.exec_errors = 0;
}

static void 	init_struct(t_data *data)
{
	data->token = NULL;
	data->ast = NULL;
	data->env = NULL;
	data->hist = NULL;
}

bool	init(t_data *data, char **argv, char **envp)
{
	(void)argv;
	init_errors(data);
	init_struct(data);
	return (init_env(data, envp));
}
