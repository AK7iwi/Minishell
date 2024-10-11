/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:08:47 by diguler           #+#    #+#             */
/*   Updated: 2024/10/11 11:17:09 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool update_dir(t_env *env, char *old_cwd) //two errors to handle 
{
	char *cwd;
	char *new_pwd;
	char *n_old_pwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	
	new_pwd = ft_strjoin("PWD=", cwd);
	n_old_pwd = ft_strjoin("OLDPWD=", old_cwd);
	if (set_env_var(&env, "PWD", new_pwd))
		return (EXIT_FAILURE);
	if (set_env_var(&env, "OLD_PWD", n_old_pwd))
		return (EXIT_FAILURE);
		
	free(cwd);
	return (EXIT_SUCCESS);
}

static bool	set_dir(char **dir, char *arg)
{
	if (!arg || ft_strncmp(arg, "~", 1) == 0)
        (*dir) = getenv("HOME");
    else if (ft_strncmp(arg, "-", 1) == 0)
        (*dir) = getenv("OLDPWD");
	else
        (*dir) = arg;

	return ((*dir));
}
bool	cd(t_data *data, char **args)
{
    char *old_cwd;
    char *dir;

	if (args[2])
		return (data->error.exec_errors |= ERROR_CD1, EXIT_FAILURE);
	
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd 
		|| !set_dir(&dir, args[1]) 
		|| chdir(dir) 
		|| update_dir(data->env, old_cwd))
		return (data->error.exec_errors |= ERROR_CD2, EXIT_FAILURE);
	
	free(old_cwd);
    return (EXIT_SUCCESS);
}

