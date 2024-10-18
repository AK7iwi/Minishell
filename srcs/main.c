/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/18 11:36:13 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void print_token_list(t_token *head)
// {
//     t_token *current = head;

// 	printf("PRINT_TEST:\n");
//     while (current)
//     {
//         printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
//         current = current->next;
//     }
// }

void	print_cmd_info(t_cmd *cmd)
{
	int	i;

	i = 0;
	// Affichage de la commande et des arguments
	if (cmd->args && cmd->args[0])
	{
		printf("Command: %s\n", cmd->args[0]);
		printf("Arguments: ");
		i = 1;
		while (cmd->args[i])
		{
			printf("%s ", cmd->args[i]);
			i++;
		}
		printf("\n");
	}
	else
	{
		printf("No command found.\n");
	}
	// Affichage du fichier d'entrée
	if (cmd->input_file)
	{
		printf("Input file: %s\n", cmd->input_file);
	}
	else
	{
		printf("No input redirection.\n");
	}
	// Affichage du fichier de sortie et si append est activé
	if (cmd->output_file)
	{
		printf("Output file: %s\n", cmd->output_file);
		if (cmd->append)
			printf("Append mode: Yes\n");
		else
			printf("Append mode: No\n");
	}
	else
	{
		printf("No output redirection.\n");
	}
}

static void	init_struct(t_data *data)
{
	data->error.error_g = 0;
	data->token = NULL;
	data->ast = NULL;
}

static inline bool	is_arg(t_error *error, int argc)
{
	if (argc != 1)
		return (error->error_g |= ERROR_ARG, true);
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	(void)argv;
	(void)envp; // tmp
	init_struct(&data);
	if (is_arg(&data.error, argc))
		return (msg_error(data.error), EXIT_FAILURE);
	while (1)
	{
		input = readline("\033[38;5;206m Minishell >\033[0m "); // protect input
		add_history(input);
		// create_heredoc("e");
		if (!input)
			return (free_loop(&data), EXIT_FAILURE);
		if (tokenizer(&data, input) || syn_analyzer(&data)
			|| ast_creator(&data))
			msg_error(data.error);
		else if (ast_exec(&data, data.ast))
			msg_error(data.error);
		// print_ast(data.ast, 5);
		// print_token_list(data.token);
		// parse_command(&data.token, &data.ast->cmd);
		// parse_tokens_to_cmd(data.token, &data.ast->cmd);
		// print_cmd_info(&data.ast->cmd);
		exec_ast_pipeline(data.ast, envp, &data);
		free_loop(&data);
	}
	return (EXIT_SUCCESS);
}
