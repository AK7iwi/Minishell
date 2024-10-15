/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:41:20 by diguler           #+#    #+#             */
/*   Updated: 2024/10/15 12:51:36 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*find_command_in_path(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = getenv("PATH");
	// printf("path_env:%s\n", path_env);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/"); //protect and free + print to test
		full_path = ft_strjoin(full_path, cmd); //protect and free
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}

	return (NULL);
}

bool	cmds(t_data *data, char **args)
{
	char	*cmd_path;
	pid_t 	pid;
    int 	status;
	char	**cpy_env;

	cmd_path = find_command_in_path(args[0]);

	// printf("cmd_path:%s\n", cmd_path);
	if (cmd_path == NULL)
	{
		printf("command not found: %s\n", args[0]); //in stderr
		return (false);
	}

	pid = fork();
	if (pid == 0)
    {
		cpy_env = copy_env(data->env); //protect and free
        if (execve(cmd_path, args, cpy_env) == -1)
        {
            perror("execve"); //execve error
            free(cmd_path);
            return (false); //exit?
        }
    }
	else if (pid == -1)
	{
		perror("fork"); //fork error 
        free(cmd_path);
        return (false); //exit?
	}
	free(cmd_path);
    waitpid(pid, &status, 0);
    if (!WIFEXITED(status) || WEXITSTATUS(status))
		return (false);
	
	return (true);
}