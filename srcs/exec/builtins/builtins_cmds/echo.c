#include "minishell.h"

static bool	check_n_flag(char **args, size_t *i)
{
    bool n_flag;
	
	n_flag = false;

    while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n') 
    {
        size_t j;
		j = 2;
		
        while (args[*i][j] && args[*i][j] == 'n')
            j++;
		
		if (args[*i][j] == '\0')
        	n_flag = true;
		else
			break;
        (*i)++;
    }

    return (n_flag);
}

bool	echo(char **args)
{
	size_t 	i;
	bool	no_newline;

	i = 1;
	no_newline = check_n_flag(args, &i);
	
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	
	if (!no_newline)
		printf("\n");

	return (EXIT_SUCCESS);
}