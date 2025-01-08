#include "minishell.h"

static	bool	create_env(t_data *data)
{
	char *cwd;
	char *pwd;
	char *shlvl;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (data->err.exec_errors |= ERR_PWD, EXIT_FAILURE);
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!pwd)
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	if (add_env_var(&data->env, pwd))
		return (free(pwd), data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	free(pwd);
	
	shlvl = "SHLVL=1";
	if (add_env_var(&data->env, shlvl))
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}

bool	init_env(t_data *data, char **envp)
{
	size_t	i;

	if (!*envp)
		return (create_env(data));

	i = 0;
	while (envp[i])
	{
		if (add_env_var(&data->env, envp[i]))
			return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
