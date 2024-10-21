/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_freer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:15:11 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/21 10:06:07 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_subshell(t_subshell *subsh)
{
	ast_freer(&subsh->root);
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
	free(cmd->output_file);
	free(cmd->input_file);
	free(cmd->delim);
	cmd->append = 0;
	cmd->nb_redir = 0;
	cmd->f_redir = 0;
	cmd->args = NULL; 
	cmd->output_file = NULL;
	cmd->input_file = NULL;
	cmd->delim = NULL;
}
static void free_operator(t_operator *op)
{
    if (op->left)
        ast_freer(&op->left);
    if (op->right)
        ast_freer(&op->right);
}

void ast_freer(t_ast **ast)
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
