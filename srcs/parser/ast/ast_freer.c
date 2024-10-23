/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_freer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:15:11 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/23 12:01:24 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_subshell(t_subshell *subsh)
{
	free_ast(&subsh->root);
}
static void free_cmd(t_cmd *cmd)
{
	size_t i;
	
	i = 0;
	//free args 
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
	i = 0;
	//free redir
	while (cmd->redirs[i]) //if redir 
	{
		free(cmd->redirs[i]);
		i++;
	}
	free(cmd->redirs);
	cmd->redirs = NULL;
	//if out free
	//if in free
	//if delim free 
	
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
