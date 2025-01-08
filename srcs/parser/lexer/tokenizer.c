#include "minishell.h"

bool	tokenizer(t_data *data, char *input)
{
	size_t 		input_len;
	size_t		i;
	
	input_len = ft_strlen(input);
	if (input_len <= 0)
		return (EXIT_FAILURE);
	
	i = 0;
	while (i < input_len)
	{
		skip_space(input, &i);
		if (handle_str(data, input, &i))
			return (EXIT_FAILURE);
		if (handle_spe_char(data, input, &i))
			return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}
