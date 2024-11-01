/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/01 12:27:31 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tab(char **tab)
{
    size_t i;
	
	i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}
void	free_loop(t_data *data)
{
	if (data->error.gen_errors || data->error.parsing_errors || data->error.exec_errors)
		free_errors(&data->error);
	if (data->token)
		free_token(&data->token);
	if (data->ast)
		free_ast(&data->ast);
}

void	free_all(t_data *data)
{
	free_loop(data);
	if (data->env)
		free_env(&data->env);
	
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}