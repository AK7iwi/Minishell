#include "minishell.h"

uint8_t get_prec(t_tok_type type)
{
	//verif
	if (is_pipe(type))
		return (1);
	else if (is_and(type) || is_or(type))
		return (2);

	return (3);
}

t_op_type get_op_type(t_tok_type type)
{
	t_op_type operator_type;

	operator_type = 0; //verif 
	
	if (is_pipe(type))
		operator_type = OP_PIPE;	
	else if (is_and(type))
		operator_type = OP_AND;
	else if (is_or(type))
		operator_type = OP_OR;

	return (operator_type);
}