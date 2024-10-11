/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:38:35 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/11 10:03:38 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool exec_subshell(t_data *data, t_subshell *subsh)
{
	ast_exec(data, subsh->root);
	//change the subshell level
	
	return (EXIT_SUCCESS);
}

static bool exec_cmd(t_data *data, t_cmd *cmd)
{	
	if (is_builtins(data, cmd->args))
		return (EXIT_SUCCESS);
	
	return (EXIT_FAILURE);
}
static bool exec_operator(t_data *data, t_operator *op)
{
	if (op->left)
    	ast_exec(data, op->left);
    if (op->right)
        ast_exec(data, op->right);
	else
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}
bool ast_exec(t_data *data, t_ast *ast)
{
	t_ast *root;
	root = ast;

	if (root->type == AST_OPERATOR)
	{
		if (exec_operator(data, &root->operator))
			return (EXIT_FAILURE);
	}
	else if (root->type == AST_COMMAND)
	{
		if (exec_cmd(data, &root->cmd))
			return (EXIT_FAILURE);
	}
	else if (root->type == AST_SUBSH)
	{
		if (exec_subshell(data, &root->subshell))
			return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}