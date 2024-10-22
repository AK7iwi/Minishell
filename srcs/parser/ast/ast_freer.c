/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_freer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:15:11 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/22 10:50:28 by mfeldman         ###   ########.fr       */
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
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free(cmd->redir->output_file);
	free(cmd->redir->input_file);
	free(cmd->redir->delim);
	cmd->args = NULL; 
	cmd->redir->nb_redir = 0;
	cmd->redir->first_redir = 0;
	cmd->redir->output_file = NULL;
	cmd->redir->input_file = NULL;
	cmd->redir->delim = NULL;
	cmd->redir->append = false; 
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
