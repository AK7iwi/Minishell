/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:16:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 12:46:06 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check for history
bool	is_fork_builtins(char **args)
{
	return (ft_strncmp(args[0], "echo", 5) == 0
			|| ft_strncmp(args[0], "pwd", 4) == 0
			|| ft_strncmp(args[0], "env", 4) == 0
			|| ft_strncmp(args[0], "history", 8) == 0);
}
bool 	is_non_fork_builtins(char **args)
{
	return (ft_strncmp(args[0], "cd", 3) == 0
			|| ft_strncmp(args[0], "export", 7) == 0
			|| ft_strncmp(args[0], "unset", 6) == 0
			|| ft_strncmp(args[0], "exit", 5) == 0);	
}
bool	builtins(t_data *data, char **args)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (!echo(args));
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (!cd(data, args)); 
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (!pwd(&data->error));
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (!ft_export(data, args));
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (!unset(data, args));
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (!env(data->env));
	// else if (ft_strncmp(args[0], "history", 8) == 0)
	// 	return (!history(args));
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (!ft_exit(data, args));

	return (false);
}