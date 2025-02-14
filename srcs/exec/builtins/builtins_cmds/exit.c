#include "minishell.h"

bool	ft_exit(t_data *data, char **args)
{
	uint8_t exit_status; //check the exit_status 
	
	exit_status = 0;

	if (args[1])
	{
		if (!is_number(args[1]))
		{
			exit_status = 2;	
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			return (exit_status);
		}
		else if (args[2])
		{
			exit_status = 1;
			return (data->err.exec_errors |= ERR_EXIT, exit_status);
		}
		else
			exit_status = ft_atoi(args[1]);
	}
	printf("exit\n");
	free_all(data);
	exit(exit_status);
}
