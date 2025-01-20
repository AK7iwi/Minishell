#include "minishell.h"

static size_t get_cmd_len(t_tok *current)
{
	size_t cmd_len;

	cmd_len = 0;
	
    while (current && is_cmd(current->type))
    {
        cmd_len++;
        current = current->next;
    } 
	return (cmd_len);
}

bool	create_cmd_node(t_ast **new_node, t_tok **current)
{	
	size_t	cmd_len;
	size_t	i;
	
	cmd_len = get_cmd_len((*current));
	(*new_node)->type = AST_COMMAND;
	(*new_node)->cmd.args = NULL;
	(*new_node)->cmd.redirs = NULL;
	(*new_node)->cmd.redir = NULL;
	i = 0;
	while (i < cmd_len)
	{
		// one cond 
		if (parse_args(new_node, current, &i))
		{
			printf("parse_arg\n");
			return (EXIT_FAILURE);
		}
		if (parse_redirs(new_node, current, &i))
		{
			printf("parse_redirs\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}