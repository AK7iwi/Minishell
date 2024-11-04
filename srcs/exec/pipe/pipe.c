/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:41:20 by diguler           #+#    #+#             */
/*   Updated: 2024/11/04 12:26:00 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	fork_and_exec_right(t_data *data, int tube[2])
{
    pid_t pid;
	int status;
	
	pid = fork();
    if (pid == 0)
    {
        if (dup2(tube[0], STDIN_FILENO) == -1) //to test
			dup2_error(data, tube[0]);
        close(tube[0]);
        exec(data, data->ast->operator.right);
		free_all(data);
        exit(EXIT_SUCCESS);
    }
	if (pid == -1) //to test 
        return (data->error.exec_errors |= ERROR_FORK, false);
	
	waitpid(pid, &status, 0);
	close(tube[0]);
	return (WIFEXITED(status) && !WEXITSTATUS(status));
}
static bool	fork_and_exec_left(t_data *data, int tube[2])
{
    pid_t pid;
	int status;
	
	pid = fork(); 
    if (pid == 0)  
    {
        close(tube[0]);
        if (dup2(tube[1], STDOUT_FILENO) == -1)
			dup2_error(data, tube[1]);  //to test
        close(tube[1]); 
        exec(data, data->ast->operator.left);
		free_all(data);
        exit(EXIT_SUCCESS);
    }
	else if (pid == -1) //test //close tube[1]
		return (data->error.exec_errors |= ERROR_FORK, false);

	waitpid(pid, &status, 0);
	close(tube[1]);
	return (WIFEXITED(status) && !WEXITSTATUS(status));
}
bool	handle_pipe(t_data *data)
{
	int tube[2];

	if (pipe(tube) == -1) //to test 
		return (data->error.exec_errors |= ERROR_PIPE, EXIT_FAILURE);

	if (!fork_and_exec_left(data, tube))
		return (EXIT_FAILURE);
	if (!fork_and_exec_right(data, tube))
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}