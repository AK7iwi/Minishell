/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:41:20 by diguler           #+#    #+#             */
/*   Updated: 2024/10/17 18:31:03 by mfeldman         ###   ########.fr       */
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

static bool handle_child_proc(t_data *data, char **args, pid_t *pid, char *cmd_path)
{
	(*pid) = fork();
	if ((*pid) == 0)
    {
        if (execve(cmd_path , args, NULL) == -1)
        {
			perror("execve");
			free(cmd_path);
			free_all(data);
            exit(EXIT_FAILURE);
        }
    }
	else if ((*pid) == -1)
        return (data->error.exec_errors |= ERROR_FORK, EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}	
bool	cmds(t_data *data, char **args)
{
	char	*cmd_path;
	pid_t 	pid;
    int 	status;

	cmd_path = find_command_in_path(args[0]);
	if (cmd_path == NULL)
	{
		printf("command not found: %s\n", args[0]); //in stderr
		return (free(cmd_path), false);
	}
	
	if (handle_child_proc(data, args, &pid, cmd_path))
		return (free(cmd_path), false);
	
	free(cmd_path);
    waitpid(pid, &status, 0);
    return (WIFEXITED(status) && !WEXITSTATUS(status));	
}