/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:39:43 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/04 10:52:44 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void free_and_exit();

void fork_error(t_data *data)
{
	perror("fork");
	free_all(data);
	exit(EXIT_FAILURE);
}
void pipe_error(t_data *data)
{
	perror("pipe");
	free_all(data);
	exit(EXIT_FAILURE);
}
void open_error(t_data *data)
{
	// close(fd); need to close if error??
	perror("Error opening input file");
	free_all(data);
	exit(EXIT_FAILURE);
}

void dup2_error(t_data *data, int fd)
{
	perror("Error redirecting input");
    close(fd);
	free_all(data);
    exit(EXIT_FAILURE);
}