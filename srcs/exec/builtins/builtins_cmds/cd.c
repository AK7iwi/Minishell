#include "minishell.h"

static bool update_dir(t_env *env, char *old_cwd)
{
	char *cwd;
	char *new_pwd;
	char *n_old_pwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return (free(cwd), EXIT_FAILURE);
	n_old_pwd = ft_strjoin("OLDPWD=", old_cwd);
	if (!n_old_pwd)
		return (free(cwd), free(new_pwd), EXIT_FAILURE);
	//one cond
	if (set_env_var(&env, "PWD", new_pwd))
		return (free(cwd), free(new_pwd), free(n_old_pwd), EXIT_FAILURE); 
	if (set_env_var(&env, "OLD_PWD", n_old_pwd))
		return (free(cwd), free(new_pwd), free(n_old_pwd), EXIT_FAILURE);
		
	free(cwd);
	free(new_pwd);
	free(n_old_pwd);
	
	return (EXIT_SUCCESS);
}

static bool	set_dir(char **dir, char *arg)
{
	if (!arg || ft_strncmp(arg, "~", 1) == 0)
        (*dir) = getenv("HOME");
    else if (ft_strncmp(arg, "-", 1) == 0)
        (*dir) = getenv("OLDPWD");
	else
        (*dir) = arg;
	
	return ((*dir));
}

bool	cd(t_data *data, char **args)
{
    char *old_cwd; //old_dir
    char *dir;

	if (args[2])
		return (data->err.exec_errors |= ERR_CD1, EXIT_FAILURE);
	
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd || !set_dir(&dir, args[1]) || chdir(dir) 
		|| update_dir(data->env, old_cwd))
	{
		printf("Ya une erreur afou\n");
		free(old_cwd);
		return (data->err.exec_errors |= ERR_CD2, EXIT_FAILURE);
	}
	
	free(old_cwd);
    return (EXIT_SUCCESS);
}
