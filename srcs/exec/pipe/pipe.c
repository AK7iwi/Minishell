/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:41:20 by diguler           #+#    #+#             */
/*   Updated: 2024/10/18 11:58:17 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gérer les redirections (pipes et fichiers)
// Gérer les processus enfants et les commandes internes
// Gérer les erreurs et les signaux
// Optimiser la libération des ressources et la modularité du code

void	exec_command(char **env, t_cmd *cmd)
{
	char	*path;
	char	**find_the_path;

	find_the_path = find_path(env);
	path = valid_path(find_the_path, cmd->args[0]);
	if (execve(path, cmd->args, env) == -1)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		free_tab(find_the_path);
		exit(EXIT_FAILURE);
	}
}

char	*find_command_in_path(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = getenv("PATH");
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

void	exec_cmds(char **args, char **env)
{
	char	*cmd_path;

	cmd_path = find_command_in_path(args[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "command not found: %s\n", args[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, args, env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	exec_ast_pipeline(t_ast *ast, char **env, t_data *data)
{
	int		tube[2];
	pid_t	pid;
	char	**r;

	if (ast == NULL)
		return ;
	handle_heredoc(data);
	if (ast->type == AST_OPERATOR)
		(handle_pipe_creation(tube), fork_and_exec_left(ast, env, tube, data),
			handle_pipe_parent(tube, ast, env, data));
	else if (ast->type == AST_COMMAND)
	{
		r = parse_args(ast->cmd.args, &ast->cmd);
		pid = fork();
		if (pid == 0)
		{
			if (ast->cmd.output_file)
				redir_output(ast->cmd.output_file, ast->cmd.append);
			if (ast->cmd.input_file)
				redir_input(ast->cmd.input_file);
			exec_cmds(r, env);
			exit(EXIT_FAILURE);
		}
		wait(NULL);
	}
}
