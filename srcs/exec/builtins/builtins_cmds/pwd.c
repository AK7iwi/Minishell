/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:28:19 by diguler           #+#    #+#             */
/*   Updated: 2024/10/11 10:04:41 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pwd(t_error *error)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (error->exec_errors |= ERROR_PWD, EXIT_FAILURE);
	else
		printf("%s\n", cwd);
	
	free(cwd);
	return (EXIT_FAILURE);
}