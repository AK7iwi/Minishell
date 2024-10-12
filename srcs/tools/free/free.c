/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/12 08:10:52 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_loop(t_data *data)
{
	if (data->error.gen_errors || data->error.parsing_errors || data->error.exec_errors)
		free_errors(&data->error);
	if (data->token)
		free_token(&data->token);
	if (data->ast)
		ast_freer(&data->ast);
}

void	free_all(t_data *data)
{
	printf("exit\n");
	free_loop(data);
	if (data->env)
		free_env(&data->env);
}