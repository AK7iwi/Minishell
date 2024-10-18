/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:38:35 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/18 07:09:32 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool subshell(t_data *data, t_subshell *subsh)
{
	exec(data, subsh->root);
	//change the subshell level
	
	return (EXIT_SUCCESS);
}

static bool cmd(t_data *data, t_cmd *cmd)
{	
	if (builtins(data, cmd->args))
		return (EXIT_SUCCESS);
	else if (cmds(data, cmd->args))
		return (EXIT_SUCCESS);
	
	return (EXIT_FAILURE);
}
static bool operator(t_data *data, t_operator *op)
{
	if (op->type == OP_PIPE)
		printf("PIPE\n");
	else if (op->type == OP_AND)
	{
		if (op->left && !exec(data, op->left))
			return (op->right && exec(data, op->right));
		return (EXIT_FAILURE);
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
	t_ast *root;
	root = ast;

	if (root->type == AST_OPERATOR)
	{
		if (operator(data, &root->operator))
			return (EXIT_FAILURE);
	}
	else if (root->type == AST_COMMAND)
	{
		if (cmd(data, &root->cmd))
			return (EXIT_FAILURE);
	}
	else if (root->type == AST_SUBSH)
	{
		if (subshell(data, &root->subshell))
			return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}