#include "minishell.h"

bool unset(t_data *data, char **args)
{
    size_t i;
	
	if (!args[1])
        return (data->err.exec_errors |= ERR_UNSET, EXIT_FAILURE);
	
	i = 1;
	while (args[i])
    {
        unset_env_var(&data->env, args[i]);
        i++;
    }

	return (EXIT_SUCCESS);
}

