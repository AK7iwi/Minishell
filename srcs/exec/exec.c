/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:38:35 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/31 11:55:14 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool subshell(t_data *data, t_subshell *subsh)
{
	//change the subshell level
	return (exec(data, subsh->root));
}

static void	exec_args(t_data *data, char **args)
{
	if ((is_fork_builtins(args) && builtins(data, args))
		|| cmds(data, args))
	{
		free_all(data);
		exit (EXIT_SUCCESS);
	}
}
static void exec_redirs(t_data *data, t_cmd *cmd, int tube[2])
{
	handle_redirs(data, cmd, tube);
	if (!cmd->args)
	{
		free_all(data);
		exit(EXIT_SUCCESS);	
	}
}
static bool exec_fork(t_data *data, t_cmd *cmd) //exec_cmd_node
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
static bool cmd(t_data *data, t_cmd *cmd)
{	
	if (cmd->args && is_non_fork_builtins(cmd->args))
	{
		if (builtins(data, cmd->args))
			return (EXIT_SUCCESS);
	}
	else if (exec_fork(data, cmd)) //test 
		return (EXIT_SUCCESS);
	
	return (EXIT_FAILURE);
}
static bool	operator(t_data *data, t_operator *op)
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
bool	exec(t_data *data, t_ast *ast)
{
	if (ast->type == AST_OPERATOR)
		return (operator(data, &ast->operator));
	else if (ast->type == AST_COMMAND)
		return (cmd(data, &ast->cmd));
	else if (ast->type == AST_SUBSH)
		return (subshell(data, &ast->subshell));
	
	return (EXIT_SUCCESS);
}