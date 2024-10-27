/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:57:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/27 17:16:00 by mfeldman         ###   ########.fr       */
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
	}

	printf("{i_file} ");
	if (ast->cmd.redir->i_file)
		printf("%s", ast->cmd.redir->i_file);
	printf("{o_file} ");
	if (ast->cmd.redir->o_file)
		printf("%s", ast->cmd.redir->o_file);
	printf("{delim} ");
	if (ast->cmd.redir->delim)
		printf("%s", ast->cmd.redir->delim);

	printf("\n");
}
static void print_operator(t_ast *ast, int *depth)
{	
	printf("[Operator] ");
    if (ast->operator.type == OP_PIPE)
		printf("'|'");
	else if (ast->operator.type == OP_AND)
		printf("'&&'");
	else if (ast->operator.type == OP_OR)
		printf("'||'");
	
	printf("\n");
    if (ast->operator.left)
	{
		for (int i = 0; i < (*depth) + 1; i++)
			printf("\t");
        printf("    [left] ");
        print_ast(ast->operator.left, (*depth) + 1);
    }
    if (ast->operator.right)
	{
		for (int i = 0; i < (*depth) + 1; i++)
			printf("\t");
        printf("    [right] ");
        print_ast(ast->operator.right, (*depth) + 1);
    }
}
void print_ast(t_ast *ast, int depth)
{
	if (ast->type == AST_OPERATOR)
		print_operator(ast, &depth);
	else if (ast->type == AST_COMMAND)
		print_cmd(ast);
	else if (ast->type == AST_SUBSH)
		print_subshell(ast, &depth);
}
