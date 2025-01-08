#include "minishell.h"

static void	init_struct(t_data *data)
{
	data->tok = NULL;
	data->ast = NULL;
	data->env = NULL;
	data->hist = NULL;
}

bool	init(t_data *data, char **argv, char **envp)
{
	(void)argv;
	init_errors(data);
	init_struct(data);
	return (init_env(data, envp));
}
