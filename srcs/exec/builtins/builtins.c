/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:16:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/04 10:41:14 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_builtins(t_data *data, char **args)
{
	if (ft_strncmp(args[0], "echo", 4) == 0)
		return (echo(args));
	// else if (ft_strncmp(args[0], "cd", 2) == 0)
	// 	return (cd(cmd->args), true);
	// else if (ft_strncmp(args[0], "pwd", 3) == 0)
	// 	return (pwd(data->error));
	// else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
	// 	return (ft_export(cmd->args), true);
	// else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
	// 	return (unset(cmd->args), true);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		return (env(data->env));
	// else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
	// 	return (exit(cmd->args), true);

	return (false);
}