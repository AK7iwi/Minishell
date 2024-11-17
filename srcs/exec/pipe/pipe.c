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

// static	bool	fork_and_exec_right(t_data *data, int tube[2])
// {
//     pid_t pid;
// 	int status;
	
// 	pid = fork();
//     if (pid == 0)
//     {
//         if (dup2(tube[0], STDIN_FILENO) == -1) //to test
// 			dup2_error(data, tube[0]);
//         close(tube[0]);
//         exec(data, data->ast->operator.right);
// 		free_all(data);
//         exit(EXIT_SUCCESS);
//     }
// 	if (pid == -1) //to test 
//         return (data->error.exec_errors |= ERROR_FORK, false);
	
// 	waitpid(pid, &status, 0);
// 	close(tube[0]);
// 	return (WIFEXITED(status) && !WEXITSTATUS(status));
// }
// static bool	fork_and_exec_left(t_data *data, int tube[2])
// {
//     pid_t pid;
// 	int status;
	
// 	pid = fork(); 
//     if (pid == 0)  
//     {
//         close(tube[0]);
//         if (dup2(tube[1], STDOUT_FILENO) == -1)
// 			dup2_error(data, tube[1]);  //to test
//         close(tube[1]); 
//         exec(data, data->ast->operator.left);
// 		free_all(data);
//         exit(EXIT_SUCCESS);
//     }
// 	else if (pid == -1) //test //close tube[1]
// 		return (data->error.exec_errors |= ERROR_FORK, false);

// 	waitpid(pid, &status, 0);
// 	close(tube[1]);
// 	return (WIFEXITED(status) && !WEXITSTATUS(status));
// }
static bool create_pipe(int tube[2], t_data *data)
{
	if (pipe(tube) == -1)
	{
		data->error.exec_errors |= ERROR_PIPE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static bool fork_and_exec_left_cmd(t_data *data, t_ast *current_ast, int tube[2], int prev_fd)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		dup2(tube[1], STDOUT_FILENO);
		close(tube[0]);
		close(tube[1]);
		exec(data, current_ast->operator.left);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
	{
		data->error.exec_errors |= ERROR_FORK;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static bool exec_final_command(t_data *data, t_ast *current_ast, int prev_fd)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
		exec(data, current_ast);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
	{
		data->error.exec_errors |= ERROR_FORK;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void close_unused_fds(int prev_fd, int tube[2])
{
	close(tube[1]);
	if (prev_fd != -1)
		close(prev_fd);
}

bool handle_pipe(t_data *data)
{
	int tube[2];
	int prev_fd = -1;
	t_ast *current_ast = data->ast;
	int status;

	while (current_ast && current_ast->type == AST_OPERATOR && current_ast->operator.type == OP_PIPE)
	{
		if (create_pipe(tube, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (fork_and_exec_left_cmd(data, current_ast, tube, prev_fd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		close_unused_fds(prev_fd, tube);
		prev_fd = tube[0];
		current_ast = current_ast->operator.right;
	}
	if (current_ast && prev_fd != -1)
	{
		if (exec_final_command(data, current_ast, prev_fd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		close(prev_fd);
	}
	while (wait(&status) > 0);
	return (WIFEXITED(status) && !WEXITSTATUS(status));
}

