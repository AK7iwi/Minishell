/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:38:35 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/29 12:35:35 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool subshell(t_data *data, t_subshell *subsh)
{
	//change the subshell level
	return (exec(data, subsh->root));
}
static bool fork_exec(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int 	status;
		
	pid = fork();
	if (pid == 0)
	{
		if (cmd->redirs && handle_redirs(data, cmd))
		{
			free_all(data);
			exit(EXIT_SUCCESS);
		}
		if (cmd->args) 
		{
			if ((is_fork_builtins(cmd->args) && builtins(data, cmd->args)) //test if builtins fail(pwd)
				|| cmds(data, cmd->args))
			{
				free_all(data);
				exit (EXIT_SUCCESS);
			}
		}
		//free_all?? 
		exit(EXIT_FAILURE); //test (with execve fail)
	}
	else if (pid == -1)
		return (data->error.exec_errors |= ERROR_FORK, false); //test
	
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && !WEXITSTATUS(status));
}
static bool cmd(t_data *data, t_cmd *cmd)
{	
	if (cmd->args && is_non_fork_builtins(cmd->args)) //&&?
	{
		if (builtins(data, cmd->args))
			return (EXIT_SUCCESS);
	}
	else if (fork_exec(data, cmd)) //test 
		return (EXIT_SUCCESS);
	
	return (EXIT_FAILURE);
}
static bool operator(t_data *data, t_operator *op)
{
	if (op->type == OP_PIPE)
		return (handle_pipe(data));
	else if (op->type == OP_AND)
	{
		if (op->left && !exec(data, op->left))
			return (op->right && exec(data, op->right));
	}
	else if (op->type == OP_OR)
	{
		if (op->left && exec(data, op->left))
			 return (op->right && exec(data, op->right));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
bool exec(t_data *data, t_ast *ast)
{
	if (ast->type == AST_OPERATOR)
		return (operator(data, &ast->operator));
	else if (ast->type == AST_COMMAND)
		return (cmd(data, &ast->cmd));
	else if (ast->type == AST_SUBSH)
		return (subshell(data, &ast->subshell));
	
	return (EXIT_SUCCESS);
}