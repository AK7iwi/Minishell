#include "minishell.h"

bool	is_fork_builtins(char **args)
{
	return (ft_strncmp(args[0], "echo", 5) == 0
			|| ft_strncmp(args[0], "pwd", 4) == 0
			|| ft_strncmp(args[0], "env", 4) == 0);
}

bool 	is_non_fork_builtins(char **args)
{
	return (ft_strncmp(args[0], "cd", 3) == 0
			|| ft_strncmp(args[0], "export", 7) == 0
			|| ft_strncmp(args[0], "unset", 6) == 0
			|| ft_strncmp(args[0], "exit", 5) == 0);	
}

bool	builtins(t_data *data, char **args)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (!echo(args));
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (!cd(data, args)); 
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (!pwd(&data->err));
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (!ft_export(data, args));
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (!unset(data, args));
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (!env(data->env));
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (!ft_exit(data, args));

	return (false);
}