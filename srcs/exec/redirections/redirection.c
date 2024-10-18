/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:42:01 by diguler           #+#    #+#             */
/*   Updated: 2024/10/18 11:43:15 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    is_redirection(const char *str)
{
    const char    *redirection_symbols[5];
    unsigned int  i;

    redirection_symbols[0] = "<";
    redirection_symbols[1] = "<<";
    redirection_symbols[2] = ">";
    redirection_symbols[3] = ">>";
    redirection_symbols[4] = NULL;
    i = 0;
    while (redirection_symbols[i])
    {
        if (strcmp(str, redirection_symbols[i]) == 0)
            return (i + 1);
        i++;
    }
    return (0);
}

int    handle_input_redirection(char **args, int i, t_cmd *cmd)
{
    cmd->input_file = strdup(args[i + 1]);
    return (i + 1);
}

int    handle_output_redirection(char **args, int i, t_cmd *cmd, int append)
{
    int fd;

    if (append)
        fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (-1);
    close(fd);
    cmd->output_file = ft_strdup(args[i + 1]);
    cmd->append = append;
    return (i + 1);
}

int    count_valid_args(char **args, t_cmd *cmd)
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
        {
            if (args[i + 1] != NULL)
            {
                if (redir == 1 || redir == 2)
                    i = handle_input_redirection(args, i, cmd);
                else
                    i = handle_output_redirection(args, i, cmd, (redir == 4));
            }
        }
        else
            count++;
        i++;
    }
    return (count);
}