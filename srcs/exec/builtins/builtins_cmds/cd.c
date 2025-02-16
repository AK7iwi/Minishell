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
	// cwd = NULL;
	if (!cwd)
		return (data->err.exec_errors |= ERR_CD2, EXIT_FAILURE);
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return (free(cwd), data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	old_pwd = ft_strjoin("OLDPWD=", old_dir);
	if (!old_pwd)
	{
		free_dirs(cwd, new_pwd, old_pwd);
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	}
	if (set_env_var(&env, "PWD", new_pwd)
		|| set_env_var(&env, "OLDPWD", old_pwd))
	{
		free_dirs(cwd, new_pwd, old_pwd);
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	}
	free_dirs(cwd, new_pwd, old_pwd);
	return (EXIT_SUCCESS);
}

static bool	set_dir(char *arg)
{
	char *new_dir;

	if (!arg || ft_strncmp(arg, "~", 2) == 0)
	{
		printf("Je passe\n");
        new_dir = getenv("HOME");
	}
    else if (ft_strncmp(arg, "-", 2) == 0)
        new_dir = getenv("OLDPWD");
	else
        new_dir = arg;
	
	if (!new_dir)
	{
		printf("Je passe 2\n");
		return (EXIT_FAILURE);
	}
	return (chdir(new_dir));
}

bool	cd(t_data *data, char **args)
{
    char *old_dir;

	if (args[2])
		return (data->err.exec_errors |= ERR_CD1, EXIT_FAILURE);
	
	old_dir = getcwd(NULL, 0);
	if (!old_dir || set_dir(args[1]))
	{
		printf("Test succed1\n");
		return (free(old_dir), data->err.exec_errors |= ERR_CD2, EXIT_FAILURE);
	}
	printf("Not the first\n");
	if (update_dir(data, data->env, old_dir))
	{
		printf("Test succed4\n");
		return (free(old_dir), EXIT_FAILURE);
	}
	
	free(old_dir);
    return (EXIT_SUCCESS);
}