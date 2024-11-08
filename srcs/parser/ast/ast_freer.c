/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_freer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:15:11 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/06 14:38:16 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_subshell(t_subshell *subsh)
{
	free_ast(&subsh->root);
}
static void free_redirs(t_cmd *cmd)
{
	size_t i;
	
	i = 0;
	while (cmd->redirs[i])
	{
		free(cmd->redirs[i]);
		i++;
	}
	free(cmd->redirs);
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
	size_t i;
	
	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
}
static void free_cmd(t_cmd *cmd)
{
	if (cmd->args) //free_tab
		free_args(cmd); //cmd->args
	if (cmd->redirs)
		free_redirs(cmd);
	cmd->args_count = 0;
	cmd->redirs_count = 0;
}
static void free_operator(t_operator *op)
{
    if (op->left)
        free_ast(&op->left);
    if (op->right)
        free_ast(&op->right);
}

void	free_ast(t_ast **ast)
{
	if ((*ast)->type == AST_OPERATOR)
		free_operator(&(*ast)->operator);
	else if ((*ast)->type == AST_COMMAND)
		free_cmd(&(*ast)->cmd);
	else if ((*ast)->type == AST_SUBSH)
		free_subshell(&(*ast)->subshell);
	free(*ast);
	*ast = NULL; 
}
