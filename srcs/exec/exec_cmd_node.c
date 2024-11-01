/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:54:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/01 11:43:01 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_args(t_data *data, char **args)
{
	if ((is_fork_builtins(args) && builtins(data, args))
		|| cmds(data, args))
	{
		free_all(data);
		exit (EXIT_SUCCESS);
	}
}
static void exec_redirs(t_data *data, t_cmd *cmd)
{
	handle_redirs(data, cmd);
	if (!cmd->args)
	{
		free_all(data);
		exit(EXIT_SUCCESS);	
	}
}
bool exec_cmd_node(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int 	status;
	
	pid = fork();
	if (pid == 0)
	{
		if (cmd->redirs)
			exec_redirs(data, cmd);
		if (cmd->args)
			exec_args(data, cmd->args);
		free_all(data); 
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
		return (data->error.exec_errors |= ERROR_FORK, false); //test
	
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && !WEXITSTATUS(status));
}