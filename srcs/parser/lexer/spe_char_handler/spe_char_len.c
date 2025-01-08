#include "minishell.h"

uint8_t	get_spe_char_len(char *input, size_t *i)
{
	uint8_t	len;
	char	special_char;
	
	len = 0;
	special_char = '\0';

	if (is_special_char(input, i))
	{
		special_char = input[*i];
		(*i)++;
		if (input[*i] == special_char && input[*i] != '(' && input[*i] != ')')
		{
			(*i)++;
			len = 2;
		}
		else 
			len = 1;
	}
	return (len);
}