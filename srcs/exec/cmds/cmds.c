/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:41:20 by diguler           #+#    #+#             */
/*   Updated: 2024/10/16 12:46:29 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*find_command_in_path(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*part_path;
	char	*full_path;
	size_t	i;

	path_env = getenv("PATH");
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
			return (free_tab(paths), NULL); //free
		full_path = ft_strjoin(part_path, cmd);
		if (!full_path)
			return (NULL); //free
		free(part_path);
		if (access(full_path, X_OK) == 0)
			return (free_tab(paths), full_path);
		free(full_path);
		i++;
	}

	return (free_tab(paths), NULL);
}

bool	cmds(t_data *data, char **args)
{
	char	*cmd_path;
	pid_t 	pid;
    int 	status;
	char	**cpy_env;

	cmd_path = find_command_in_path(args[0]);
	if (cmd_path == NULL)
	{
		printf("command not found: %s\n", args[0]); //in stderr
		return (free(cmd_path), EXIT_FAILURE);
	}
	//fct 
	pid = fork();
	// pid = -1; to test
	if (pid == 0)
    {
		cpy_env = copy_env(data->env);
		if (!cpy_env)
			exit(EXIT_FAILURE); ///free
		// char *cmd_fail = ft_strjoin(cmd_path, "oui"); //to test because leaks in child process
		//free_all here?
        if (execve(cmd_path , args, cpy_env) == -1)
        {
            free(cmd_path);
			free_tab(cpy_env);
            exit(EXIT_FAILURE);
        }
		free_tab(cpy_env);
    }
	else if (pid == -1)
	{
        free(cmd_path);
        return (data->error.exec_errors |= ERROR_FORK, EXIT_FAILURE);
	}
	free(cmd_path);
    waitpid(pid, &status, 0);
    if (!WIFEXITED(status) || WEXITSTATUS(status))
		return (data->error.exec_errors |= ERROR_EXECVE, EXIT_FAILURE); 
	
	return (EXIT_SUCCESS);
}