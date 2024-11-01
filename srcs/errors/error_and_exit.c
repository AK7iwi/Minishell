/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:39:43 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/01 12:41:10 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void pipe_error(t_data *data)
{
	(void)data;
	
}

void open_error(t_data *data)
{
	// close(fd); need to close if error??
	perror("Error opening input file");
	free_all(data);
	exit(EXIT_FAILURE);
}

void dup2_error(t_data *data)
{
	(void)data;
	
}