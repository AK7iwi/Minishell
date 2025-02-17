#include "minishell.h"

static void free_dirs(char *cwd, char *new_pwd, char *old_pwd)
{
	if (cwd)
		free(cwd);
	if (new_pwd)
		free(new_pwd);
	if (old_pwd)
		free(old_pwd);
}

static bool	update_dir(t_data *data, t_env *env, char *old_dir)
{
	char *cwd;
	char *new_pwd;
	char *old_pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (data->err.exec_errors |= ERR_CD2, EXIT_FAILURE);
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return (free(cwd), data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	old_pwd = ft_strjoin("OLDPWD=", old_dir);
	if (!old_pwd || set_env_var(&env, "PWD", new_pwd)
		|| set_env_var(&env, "OLDPWD", old_pwd))
	{
		printf("ca passsse\n");
		free_dirs(cwd, new_pwd, old_pwd);
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	}
	free_dirs(cwd, new_pwd, old_pwd);
	return (EXIT_SUCCESS);
}

static bool	set_dir(char *arg, char **new_dir)
{
	if (!arg || ft_strncmp(arg, "~", 2) == 0)
        (*new_dir) = getenv("HOME");
    else if (ft_strncmp(arg, "-", 2) == 0)
        (*new_dir) = getenv("OLDPWD");
	else
		(*new_dir) = arg;
	
	return (!(*new_dir));
}

bool	cd(t_data *data, char **args)
{
    char *old_dir;
	char *new_dir;

	if (args[1] && args[2])
		return (data->err.exec_errors |= ERR_CD1, EXIT_FAILURE);
	
	old_dir = getcwd(NULL, 0);
	if (!old_dir)
		return (data->err.exec_errors |= ERR_CD2, EXIT_FAILURE);
	if (set_dir(args[1], &new_dir))
		return (free(old_dir), data->err.exec_errors |= ERR_CD3, EXIT_FAILURE);
	if (chdir(new_dir))
		return (free(old_dir), data->err.exec_errors |= ERR_CD2, EXIT_FAILURE);
	if (update_dir(data, data->env, old_dir))
		return (free(old_dir), EXIT_FAILURE);
	
	free(old_dir);
    return (EXIT_SUCCESS);
}