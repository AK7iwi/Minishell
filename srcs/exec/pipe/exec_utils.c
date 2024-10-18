/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:42:24 by diguler           #+#    #+#             */
/*   Updated: 2024/10/18 09:56:55 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	size_t	i;
	if(!*tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	open_file(char *av, int read)
{
	int	fd;

	fd = 0;
	if (read == 0)
		fd = open(av, O_RDONLY, 0644);
	if (read == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Open failed :");
		exit(1);
	}
	return (fd);
}

char	**find_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (path);
}

char	*valid_path(char **all_paths, char *cmd)
{
	int		i;
	char	*path;
	char	**valid_cmd;
	char	*full_path;

	full_path = NULL;
	if (!*cmd)
		return (cmd);
	valid_cmd = ft_split(cmd, ' ');
	i = 0;
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(path, valid_cmd[0]);
		free(path);
		if (access(full_path, X_OK | F_OK) == 0)
		{
			free_tab(valid_cmd);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab(valid_cmd);
	return (cmd);
}