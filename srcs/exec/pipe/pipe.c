/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:41:20 by diguler           #+#    #+#             */
/*   Updated: 2024/10/28 11:00:09 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	fork_and_exec_right(t_data *data, int fd_in)
{
    pid_t pid;
	
	pid = fork();
    if (pid == -1) //to test 
        return (data->error.exec_errors |= ERROR_FORK, EXIT_FAILURE);
    else if (pid == 0)
    {
        if (dup2(fd_in, STDIN_FILENO)) //to test
			return (EXIT_FAILURE);
        close(fd_in); 
        exec(data, data->ast->operator.right);
		free_all(data);
        exit(EXIT_SUCCESS);
    }
	return (EXIT_SUCCESS);
}
static	bool handle_pipe_parent(t_data *data, int tube[2])
{
    int fd_in;
	
	fd_in = tube[0];
    close(tube[1]); 
    wait(NULL);
    if (fork_and_exec_right(data, fd_in)) 
		return (EXIT_FAILURE); //to test
    close(fd_in);
    wait(NULL);
	
	return (EXIT_SUCCESS);
}
static bool	fork_and_exec_left(t_data *data, int tube[2])
{
    pid_t pid;
	
	pid = fork();
    if (pid == 0)  
    {
        if (dup2(tube[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);  //to test
        close(tube[0]); 
        close(tube[1]); 
        exec(data, data->ast->operator.left);
		free_all(data);
        exit(EXIT_SUCCESS);
    }
	else if (pid == -1) //test 
		return (data->error.exec_errors |= ERROR_FORK, EXIT_FAILURE); //one return 

	return (EXIT_SUCCESS);
}
bool handle_pipe(t_data *data)
{
	int tube[2];

	if (pipe(tube) == -1) //to test 
		return (data->error.exec_errors |= ERROR_PIPE, EXIT_FAILURE);

	return (fork_and_exec_left(data, tube) || handle_pipe_parent(data, tube));
}