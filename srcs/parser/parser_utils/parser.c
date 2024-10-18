/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:44:44 by diguler           #+#    #+#             */
/*   Updated: 2024/10/18 11:45:10 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **fill_parsed_args(char **args, char **parsed_args)
{
    int count;
    int redir;
    int i;

    count = 0;
    i = 0;
    while (args[i] != NULL)
    {
        redir = is_redirection(args[i]);
        if (redir)
            i++;
        else
        {
            parsed_args[count] = strdup(args[i]);
            if (!parsed_args[count])
                return (NULL);
            count++;
        }
        i++;
    }
    parsed_args[count] = NULL;
    return (parsed_args);
}

char    **parse_args(char **args, t_cmd *cmd)
{
    int     count;
    char    **parsed_args;

    cmd->output_file = NULL;
    cmd->input_file = NULL;
    count = count_valid_args(args, cmd);
    parsed_args = malloc((count + 1) * sizeof(char *));
    if (!parsed_args)
    {
        perror("Failed to allocate memory");
        return (NULL);
    }
    return (fill_parsed_args(args, parsed_args));
}