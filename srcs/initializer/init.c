/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:18:51 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:10:54 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void 	init_errs(t_data *data)
{
	data->err.gen_errors = 0;
	data->err.parsing_errors = 0;
	data->err.exec_errors = 0;
}

static void 	init_struct(t_data *data)
{
	data->tok = NULL;
	data->ast = NULL;
	data->env = NULL;
	data->hist = NULL;
}

bool	init(t_data *data, char **argv, char **envp)
{
	(void)argv;
	init_errs(data);
	init_struct(data);
	return (init_env(data, envp));
}
