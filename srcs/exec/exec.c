#include "minishell.h"

static bool subshell(t_data *data, t_subshell *subsh)
{
	//change the subshell level
	return (exec(data, subsh->root));
}

static bool cmd(t_data *data, t_cmd *cmd)
{	
	if (cmd->args && is_non_fork_builtins(cmd->args)) //need cmd->args?
	{
		if (builtins(data, cmd->args))
			return (EXIT_SUCCESS);
	}
	else if (exec_cmd_node(data, cmd)) //test 
		return (EXIT_SUCCESS);
	
	return (EXIT_FAILURE);
}

static bool	operator(t_data *data, t_op *op)
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
		return (operator(data, &ast->op));
	else if (ast->type == AST_COMMAND)
		return (cmd(data, &ast->cmd));
	else if (ast->type == AST_SUBSH)
		return (subshell(data, &ast->subshell));
	
	return (EXIT_SUCCESS);
}
