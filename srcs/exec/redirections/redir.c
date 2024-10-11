/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:40:50 by diguler           #+#    #+#             */
/*   Updated: 2024/10/11 12:12:26 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redir_output(char *filename, int append)
{
    int fd;
    if (append)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}
void redir_input(const char *filename)
{
    int fd;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}


