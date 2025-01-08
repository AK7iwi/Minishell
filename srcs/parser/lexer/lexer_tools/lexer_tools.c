#include "minishell.h"

bool	is_special_char(char *input, size_t *i)
{
	return (input[*i] == '|' 
			|| input[*i] == '<' 
			|| input[*i] == '>' 
			|| input[*i] == '&' 
			|| input[*i] == '(' 
			|| input[*i] == ')');
}

void	skip_space(char *input, size_t *i)
{
	while (input[*i] == ' ')
		(*i)++;
}