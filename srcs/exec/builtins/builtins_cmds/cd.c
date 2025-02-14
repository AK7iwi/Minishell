#include "minishell.h"

static bool update_dir(t_env *env, char *old_dir)
{
	char *cwd;
	char *new_pwd;
	char *old_pwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return (free(cwd), EXIT_FAILURE);
	old_pwd = ft_strjoin("OLDPWD=", old_dir);
	if (!old_pwd)
		return (free(cwd), free(new_pwd), EXIT_FAILURE);
	if (set_env_var(&env, "PWD", new_pwd)
		|| set_env_var(&env, "OLDPWD", old_pwd))
		return (free(cwd), free(new_pwd), free(old_pwd), EXIT_FAILURE); 
		
	free(cwd);
	free(new_pwd);
	free(old_pwd);
	
	return (EXIT_SUCCESS);
}

static bool	set_dir(char **new_dir, char *arg)
{
	if (!arg || ft_strncmp(arg, "~", 2) == 0)
        (*new_dir) = getenv("HOME");
    else if (ft_strncmp(arg, "-", 2) == 0)
        (*new_dir) = getenv("OLDPWD");
	else
        (*new_dir) = arg;
	
	//return (NULL);
	return ((*new_dir));
}

bool	cd(t_data *data, char **args)
{
    char *old_dir;
    char *new_dir;

	if (args[2])
		return (data->err.exec_errors |= ERR_CD1, EXIT_FAILURE);
	
	// old_dir = getcwd(NULL, 0);
	old_dir = NULL;
	if (!old_dir || !set_dir(&new_dir, args[1]) || chdir(new_dir) 
		|| update_dir(data->env, old_dir))
		return (free(old_dir), data->err.exec_errors |= ERR_CD2, EXIT_FAILURE);
	
	free(old_dir);
    return (EXIT_SUCCESS);
}
