/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/11 16:52:55 by diguler          ###   ########.fr       */
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

// Fonction pour ajouter un argument au tableau d'arguments
char **add_argument(char **args, char *new_arg)
{
    int i = 0;

    // Comptez le nombre d'arguments existants
    if (args)
    {
        while (args[i])
            i++;
    }

    // Allouez un nouvel espace pour le nouvel argument
    char **new_args = malloc((i + 2) * sizeof(char *));
    if (!new_args)
        return NULL;

    // Copiez les anciens arguments
    for (int j = 0; j < i; j++)
        new_args[j] = args[j];

    // Ajoutez le nouvel argument
    new_args[i] = strdup(new_arg);
    new_args[i + 1] = NULL;

    // Libérez l'ancien tableau d'arguments s'il existe
    if (args)
        free(args);

    return new_args;
}

// Fonction pour parser les tokens et remplir la structure s_cmd
void parse_tokens_to_cmd(t_token *tokens, t_cmd *cmd)
{
    cmd->args = NULL;         // Initialiser args à NULL
    cmd->input_file = NULL;   // Fichier d'entrée à NULL par défaut
    cmd->output_file = NULL;  // Fichier de sortie à NULL par défaut
    cmd->append = 0;          // Par défaut, pas d'ajout (append)

    while (tokens)
    {
        if (tokens->type == TOKEN_WORD)
        {
            // Ajouter le mot (commande ou argument) à args
            cmd->args = add_argument(cmd->args, tokens->str);
            tokens = tokens->next;
        }
        else if (tokens->type == TOKEN_SIMPLE_REDIRECT_IN)
        {
            // Redirection d'entrée '<'
            if (tokens->next && tokens->next->type == TOKEN_WORD)
            {
                cmd->input_file = strdup(tokens->next->str);
                tokens = tokens->next->next;
            }
            else
            {
                fprintf(stderr, "Error: Missing input file for redirection.\n");
                return;
            }
        }
        else if (tokens->type == TOKEN_SIMPLE_REDIRECT_OUT)
        {
            // Redirection de sortie '>'
            if (tokens->next && tokens->next->type == TOKEN_WORD)
            {
                cmd->output_file = strdup(tokens->next->str);
                cmd->append = 0;  // Overwrite
                tokens = tokens->next->next;
            }
            else
            {
                fprintf(stderr, "Error: Missing output file for redirection.\n");
                return;
            }
        }
        else if (tokens->type == TOKEN_DOUBLE_REDIRECT_OUT)
        {
            // Redirection de sortie '>>'
            if (tokens->next && tokens->next->type == TOKEN_WORD)
            {
                cmd->output_file = strdup(tokens->next->str);
                cmd->append = 1;  // Append
                tokens = tokens->next->next;
            }
            else
            {
                fprintf(stderr, "Error: Missing output file for redirection.\n");
                return;
            }
        }
        else
        {
            tokens = tokens->next; // Passer au token suivant
        }
    }

    // Vérification que la commande est présente
    if (!cmd->args || !cmd->args[0])
    {
        fprintf(stderr, "Error: No command found.\n");
        return;
    }
}

void print_cmd_info(t_cmd *cmd)
{
    int i = 0;

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

static inline bool is_arg(t_error *error, int argc)
{
	if (argc != 1)
		return (error->error_g |= ERROR_ARG, true);

	return (false);
}
int main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	(void)argv;
    (void)envp; //tmp
	
	init_struct(&data);
	if (is_arg(&data.error, argc))
		return (msg_error(data.error), EXIT_FAILURE);
	
    while (1)
    {
		input = readline("Minishell> "); //protect input
		add_history(input);
        //create_heredoc("e");
		if (!input)
			return (free_loop(&data), EXIT_FAILURE);
        if (tokenizer(&data, input) || syn_analyzer(&data) || ast_creator(&data))
			msg_error(data.error);
		else if (ast_exec(&data, data.ast))
			msg_error(data.error);
		// print_ast(data.ast, 5);
		// print_token_list(data.token);
		// parse_command(&data.token, &data.ast->cmd);
        parse_tokens_to_cmd(data.token, &data.ast->cmd);
        // print_cmd_info(&data.ast->cmd);
		exec_ast_pipeline(data.ast, envp, &data);
		//free_loop(&data);
    }
	
    return (EXIT_SUCCESS);
}
