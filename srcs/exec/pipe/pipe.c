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
        exec(data, data->ast->op.right);
		free_all(data);
        exit(EXIT_SUCCESS);
    }
	if (pid == -1) //to test 
        return (data->err.exec_errors |= ERR_FORK, false);
	
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
        exec(data, data->ast->op.left);
		free_all(data);
        exit(EXIT_SUCCESS);
    }
	else if (pid == -1) //test //close tube[1]
		return (data->err.exec_errors |= ERR_FORK, false);

	waitpid(pid, &status, 0);
	close(tube[1]);
	return (WIFEXITED(status) && !WEXITSTATUS(status));
}

bool	handle_pipe(t_data *data)
{
	int tube[2];

	if (pipe(tube) == -1) //to test 
		return (data->err.exec_errors |= ERR_PIPE_CMD, EXIT_FAILURE); // pipe_error??

	if (!fork_and_exec_left(data, tube))
		return (EXIT_FAILURE);
	if (!fork_and_exec_right(data, tube))
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}
