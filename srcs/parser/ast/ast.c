/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:25:53 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/27 20:50:23 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ast tools
uint8_t get_prec(t_tok_type type)
{
	//verif
	if (is_pipe(type))
		return (1);
	else if (is_and(type) || is_or(type))
		return (2);

	return (3);
}

t_op_type get_operator_type(t_tok_type type)
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
void	handle_operator(t_ast **result, t_token **current, uint8_t min_prec)
{
	uint8_t 	next_min_prec;
	t_op_type	op_type;
	t_ast 		*right_side;
	
	while ((*current) && is_operator((*current)->type) && get_prec((*current)->type) >= min_prec)
	{
		next_min_prec = get_prec((*current)->type);
		op_type = get_operator_type((*current)->type);
		(*current) = (*current)->next;
		right_side = ast_algo(current, next_min_prec);
		(*result) = create_operator_node((*result), right_side, op_type); // protect
	}
}
t_ast *handle_cmd_and_subsh(t_token **current)
{
	t_ast *new_node;
	
	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	if ((*current) && (*current)->type == T_O_PAREN)
		new_node = create_subsh_node(&new_node, current);
	else
		new_node = create_cmd_node(&new_node, current);
	
	return (new_node);
}
t_ast *ast_algo(t_token **current, uint8_t min_prec)
{
	t_ast 		*result;

	result = handle_cmd_and_subsh(current);
	if (!result)
    	return (NULL); //test
	else if ((*current) && (*current)->type == T_C_PAREN)
		return (result);
	handle_operator(&result, current, min_prec); // protect

    return (result);
}
bool	ast_creator(t_data *data)
{
	t_token *current;
	current = data->token;
	data->ast = ast_algo(&current, 0);
	return (!data->ast);
}