#include "minishell.h"

bool	syn_analyzer(t_data *data)
{
    t_tok		*current;
	uint32_t	o_count;
	uint32_t	c_count;
	
	o_count = 0;
	c_count = 0;
    current = data->tok;
	
    while (current)
    {
		if (check_paren(&data->err, current, &o_count, &c_count))
			return (data->err.parsing_errors |= ERR_PAREN, EXIT_FAILURE);
		else if (check_operator(&data->err, current))
			return (data->err.parsing_errors |= ERR_OPERATOR, EXIT_FAILURE);
		else if (check_redir(&data->err, current))
			return (data->err.parsing_errors |= ERR_REDIR, EXIT_FAILURE);
		current = current->next;
    }
	
	if (o_count != c_count)
	{
		data->err.parsing_errors |= (ERR_PAREN | ERR_G_PAREN);
		return (EXIT_FAILURE);
	}
    return (EXIT_SUCCESS);
}
