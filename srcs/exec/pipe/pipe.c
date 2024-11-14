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
bool	handle_pipe(t_data *data)
{
	int tube[2];
	int prev_fd = -1;
	t_ast *current_ast = data->ast;
	pid_t pid;
	int status;

	while (current_ast && current_ast->type == AST_OPERATOR && current_ast->operator.type == OP_PIPE)
	{
		if (pipe(tube) == -1) // Crée un nouveau tube pour chaque étape de la chaîne
			return (data->error.exec_errors |= ERROR_PIPE, EXIT_FAILURE);
		
		// Crée un processus pour la commande de gauche
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1) // Utilise l'entrée du tube précédent, s'il existe
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			dup2(tube[1], STDOUT_FILENO); // Sortie vers le tube courant
			close(tube[0]);
			close(tube[1]);
			exec(data, current_ast->operator.left);
			free_all(data);
			exit(EXIT_FAILURE);
		}
		else if (pid == -1)
			return (data->error.exec_errors |= ERROR_FORK, false);
		
		// Ferme les descripteurs de tubes inutilisés dans le processus parent
		close(tube[1]);
		if (prev_fd != -1)
			close(prev_fd);
		
		// Prépare le tube courant pour le prochain tour
		prev_fd = tube[0];
		current_ast = current_ast->operator.right; // Passe à la commande suivante
	}

	// Exécute la dernière commande sans créer un autre pipe
	if (current_ast && prev_fd != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
			exec(data, current_ast);
			free_all(data);
			exit(EXIT_FAILURE);
		}
		else if (pid == -1)
			return (data->error.exec_errors |= ERROR_FORK, false);
		close(prev_fd);
	}

	// Attends tous les processus enfants
	while (wait(&status) > 0);
	return (WIFEXITED(status) && !WEXITSTATUS(status));
}
