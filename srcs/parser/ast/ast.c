#include "minishell.h"

bool	handle_operator(t_ast **result, t_tok **current, uint8_t min_prec)
{
	uint8_t 	next_min_prec;
	t_op_type	op_type;
	t_ast 		*right_side;
	
	while ((*current) 
		&& is_operator((*current)->type)
		&& get_prec((*current)->type) >= min_prec)
	{
		next_min_prec = get_prec((*current)->type);
		op_type = get_op_type((*current)->type);
		(*current) = (*current)->next;
		if (ast_algo(&right_side, current, next_min_prec))
			return (free_ast(&right_side), EXIT_FAILURE);
		(*result) = create_operator_node((*result), right_side, op_type);
		if (!(*result))
			return (free_ast(&right_side), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	handle_cmd_and_subsh(t_ast **ast, t_tok **current)
{
	(*ast) = malloc(sizeof(t_ast));
	if (!(*ast))
		return (EXIT_FAILURE);
	
	if (is_o_paren((*current)->type))
	{
		if (create_subsh_node(ast, current))
			return (EXIT_FAILURE);
	}
	else
	{
		if (create_cmd_node(ast, current))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	ast_algo(t_ast **ast, t_tok **current, uint8_t min_prec)
{
	if (handle_cmd_and_subsh(ast, current))
    	return (EXIT_FAILURE);
	else if ((*current) && is_c_paren((*current)->type))
		return (EXIT_SUCCESS);
	
	if (handle_operator(ast, current, min_prec))
		return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

bool	ast_creator(t_data *data)
{
	t_tok	*current;
	
	current = data->tok;
	if (ast_algo(&data->ast, &current, 0))
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
