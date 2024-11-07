/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:05:41 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:11:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_env(t_data *data)
{
	char *cwd;
	char *pwd;
	char *shlvl;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (data->err.exec_errors |= ERR_PWD, EXIT_FAILURE);
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!pwd)
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	if (add_env_var(&data->env, pwd))
		return (free(pwd), data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	free(pwd);
	
	shlvl = "SHLVL=1";
	if (add_env_var(&data->env, shlvl))
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}