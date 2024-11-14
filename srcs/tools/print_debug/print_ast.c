/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:27:23 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:21:09 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_subshell(t_ast *ast, int *depth)
{
	printf("[Subshell]\n");
	for (int i = 0; i < (*depth) + 1; i++)
			printf("\t");
	print_ast(ast->subshell.root, (*depth));
}

static void print_cmd(t_ast *ast)
{
	size_t i;

	i = 0;
	printf("[Cmd] ");
	if (ast->cmd.args && ast->cmd.args[0])
	{
		while (ast->cmd.args[i])
		{
			printf("%s ", ast->cmd.args[i]);
			i++;
		}	
	}
	
	i = 0;
	printf("{redir} ");
	if (ast->cmd.redirs && ast->cmd.redirs[0])
	{
		while (ast->cmd.redirs[i])
		{
			printf("%s ", ast->cmd.redirs[i]);
			i++;
		}
		printf(" {i_file} ");
		if (ast->cmd.redir->i_file)
			printf("%s", ast->cmd.redir->i_file);
		printf(" {o_file} ");
		if (ast->cmd.redir->o_file)
			printf("%s", ast->cmd.redir->o_file);
		printf(" {delim} ");
		if (ast->cmd.redir->delim)
			printf("%s", ast->cmd.redir->delim);
	}

	printf("\n");
}
static void print_op(t_ast *ast, int *depth)
{	
	printf("[Operator] ");
    if (ast->op.type == OP_PIPE)
		printf("'|'");
	else if (ast->op.type == OP_AND)
		printf("'&&'");
	else if (ast->op.type == OP_OR)
		printf("'||'");
	
	printf("\n");
    if (ast->op.left)
	{
		for (int i = 0; i < (*depth) + 1; i++)
			printf("\t");
        printf("    [left] ");
        print_ast(ast->op.left, (*depth) + 1);
    }
    if (ast->op.right)
	{
		for (int i = 0; i < (*depth) + 1; i++)
			printf("\t");
        printf("    [right] ");
        print_ast(ast->op.right, (*depth) + 1);
    }
}
void print_ast(t_ast *ast, int depth)
{
	if (ast->type == AST_OPERATOR)
		print_op(ast, &depth);
	else if (ast->type == AST_COMMAND)
		print_cmd(ast);
	else if (ast->type == AST_SUBSH)
		print_subshell(ast, &depth);
}