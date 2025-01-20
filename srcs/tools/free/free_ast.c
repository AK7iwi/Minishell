#include "minishell.h"

static void free_subshell(t_subshell *subsh)
{
	free_ast(&subsh->root);
}

static void free_redirs(t_cmd *cmd)
{
	free_tab(cmd->redirs);
	cmd->redirs = NULL;
	if (cmd->redir) 
	{
		if (cmd->redir->i_file)
			free(cmd->redir->i_file);
		if (cmd->redir->o_file)
			free(cmd->redir->o_file);
		if (cmd->redir->delim)
			free(cmd->redir->delim);
		free(cmd->redir);
	}
}

static void free_args(t_cmd *cmd)
{
	free_tab(cmd->args);
	cmd->args = NULL;
}

static void free_cmd(t_cmd *cmd)
{
	if (cmd->args)
		free_args(cmd);
	if (cmd->redirs)
		free_redirs(cmd);
	cmd->args_count = 0;
	cmd->redirs_count = 0;
}

static void free_operator(t_op *op)
{
    if (op->left)
        free_ast(&op->left);
    if (op->right)
        free_ast(&op->right);
}

void	free_ast(t_ast **ast)
{
	if ((*ast)->type == AST_OPERATOR)
		free_operator(&(*ast)->op);
	else if ((*ast)->type == AST_COMMAND)
		free_cmd(&(*ast)->cmd);
	else if ((*ast)->type == AST_SUBSH)
		free_subshell(&(*ast)->subshell);

	free(*ast);
	*ast = NULL; 
}