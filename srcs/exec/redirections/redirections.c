/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:14:25 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 13:59:24 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exec_heredoc(int tube[2], char *delim)
{
	char	*line;
	
	close(tube[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break;
		}
		write(tube[1], line, ft_strlen(line));
		write(tube[1], "\n", 1);
		free(line);
	}
	close(tube[1]);
}

static void handle_heredoc(t_data *data, char *r_delim, char *delim)
{
	int 	tube[2];
	pid_t 	pid;
	int 	status;
	
	if (pipe(tube) == -1)
		pipe_error(data);
	pid = fork();
	if (pid == 0)
	{
		exec_heredoc(tube, delim);
		free_all(data);
		exit(EXIT_SUCCESS);
	}
	else if (pid == -1)
		fork_error(data);
	waitpid(pid, &status, 0); //check status 
	close(tube[1]);
	if (ft_strncmp(r_delim, delim, ft_strlen(r_delim) + 1) == 0)
		if (dup2(tube[0], STDIN_FILENO) == -1)
			dup2_error(data, tube[0]);
    close(tube[0]);
}

static void handle_o_files(t_data *data, char *o_file, char *redir, int is_last)
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
        open_error(data);

    // Appliquer dup2 uniquement si c'est la dernière redirection
    if (is_last) 
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
            dup2_error(data, fd);
    }
    close(fd);
}

static void handle_i_files(t_data *data, char *i_file)
{
    int fd;

    fd = open(i_file, O_RDONLY);
    if (fd == -1)
        open_error(data);
    else
    {
        if (dup2(fd, STDIN_FILENO) == -1)
            dup2_error(data, fd);
    }
    close(fd);
}

void handle_redirs(t_data *data, t_cmd *cmd)
{
    size_t i;
    int is_last;

    i = 0;
    while (cmd->redirs[i])
    {
        is_last = (cmd->redirs[i + 2] == NULL);  // Détecte la dernière redirection

        // Traite les redirections de type Heredoc
        if (ft_strncmp(cmd->redirs[i], "<<", 3) == 0)
        {
            handle_heredoc(data, cmd->redirs[i + 1], cmd->redirs[i + 1]);
        }
        // Traite les redirections d'entrée
        else if (ft_strncmp(cmd->redirs[i], "<", 2) == 0)
        {
            handle_i_files(data, cmd->redirs[i + 1]);
        }
        // Traite les redirections de sortie
        else if (ft_strncmp(cmd->redirs[i], ">", 2) == 0 || ft_strncmp(cmd->redirs[i], ">>", 3) == 0)
        {
            handle_o_files(data, cmd->redirs[i + 1], cmd->redirs[i], is_last);
        }
        i += 2;
    }
}


