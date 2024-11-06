/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:49:49 by diguler           #+#    #+#             */
/*   Updated: 2024/11/06 12:49:52 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env(t_env *env)
{
	t_env *current;
		
	current = env;
	while (current)
	{
		printf("%s\n", current->env_var);
		current = current->next;
	}

	return (EXIT_SUCCESS);
}
