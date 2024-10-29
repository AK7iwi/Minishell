/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:14:25 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/29 19:12:49 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_o_files(t_data *data, char *o_file, char *redir, char *file)
{
	int fd;
	int flags;
	
	flags = O_WRONLY | O_CREAT;
	if (ft_strncmp(redir, ">", 2) == 0)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	
	fd = open(o_file, flags, 0644);
	if (fd == -1) 
    {
        perror("Error opening output file");
		free_all(data);
        exit(EXIT_FAILURE);
    }
	if (ft_strncmp(o_file, file, ft_strlen(o_file) + 1) == 0)
	{
        if (dup2(fd, STDOUT_FILENO) == -1) 
        {
            perror("Error redirecting output");
            close(fd);
			free_all(data);
            exit(EXIT_FAILURE);
        }
	}
	close(fd);
}
static void	handle_i_files(t_data *data, char *i_file, char *file)
{
	int fd;
	
	fd = open(i_file, O_RDONLY);
	if (fd == -1)
	{
		// close(fd); need to close if error??
		perror("Error opening input file"); //handle error 
		free_all(data);
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(i_file, file, ft_strlen(i_file) + 1) == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1) 
        {
            perror("Error redirecting input"); //handle error
            close(fd);
			free_all(data);
            exit(EXIT_FAILURE);
        }
	}
	close(fd);
} 
void	handle_redirs(t_data *data, t_cmd *cmd)
{
	size_t i;

	i = 0;
	while (cmd->redirs[i])
	{
		if (ft_strncmp(cmd->redirs[i], "<", 2) == 0)
			handle_i_files(data, cmd->redir->i_file, cmd->redirs[i + 1]);
		else if (ft_strncmp(cmd->redirs[i], ">", 2) == 0 
				|| ft_strncmp(cmd->redirs[i], ">>", 3) == 0)
			handle_o_files(data, cmd->redir->o_file, cmd->redirs[i], cmd->redirs[i + 1]);
		// else if (ft_strncmp(cmd->redirs[i], "<<", 3) == 0)
		// 	handle_heredoc(cmd->redirs[i + 1]);
		i++;
		i++;
	}
}