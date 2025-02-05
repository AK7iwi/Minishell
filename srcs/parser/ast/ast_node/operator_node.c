#include "minishell.h"

t_ast	*create_operator_node(t_ast *left, t_ast *right, t_op_type op_type)
{
	t_ast *new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (free_ast(&left), NULL);
	
	new_node->type = AST_OPERATOR;
	new_node->op.type = op_type;
	new_node->op.left = left;
	new_node->op.right = right;
	
	return (new_node);
}

t_op_type get_op_type(t_tok_type type)
{	
	if (is_and(type))
		return (OP_AND);
	else if (is_or(type))
		return (OP_OR);

	return (OP_PIPE);
}

bool get_prec(t_tok_type type)
{
	if (is_pipe(type))
		return (1);
	return (2);
}