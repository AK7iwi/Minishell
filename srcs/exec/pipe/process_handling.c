/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:15:26 by diguler           #+#    #+#             */
/*   Updated: 2024/10/11 11:47:19 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fork_and_exec_left(t_ast *ast, char **env, int tube[2], t_data *data)
{
    pid_t pid = fork();
    if (pid == -1)
        handle_fork_error();
    
    if (pid == 0)  
    {
        dup2(tube[1], STDOUT_FILENO); 
        close(tube[0]); 
        close(tube[1]); 
        exec_ast_pipeline(ast->operator.left, env, data); 
        exit(EXIT_SUCCESS);
    }
}

void fork_and_exec_right(t_ast *ast, char **env, int fd_in, t_data *data)
{
    pid_t pid = fork();
    if (pid == -1)
        handle_fork_error();

    if (pid == 0)
    {
        dup2(fd_in, STDIN_FILENO); 
        close(fd_in); 
        exec_ast_pipeline(ast->operator.right, env, data);
        exit(EXIT_SUCCESS);
    }
}

void handle_pipe_parent(int tube[2], t_ast *ast, char **env, t_data *data)
{
    int fd_in = tube[0];
    close(tube[1]); 
    wait(NULL); 
    fork_and_exec_right(ast, env, fd_in, data);
    close(fd_in);
    wait(NULL);
}

