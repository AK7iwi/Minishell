/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:05:00 by diguler           #+#    #+#             */
/*   Updated: 2024/10/11 10:56:58 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_export(t_data *data, char **args)
{
	size_t i;
	char *var_name;

	if (!args[1])
		if (print_sorted_env(data->env))
			return (EXIT_FAILURE);
		
	i = 1;
	while (args[i])
	{
		if (!is_valid_var(args[i]))
			printf("export: `%s': not a valid identifier\n", args[i]);
		else if (find_equal(args[i]))
		{
			//fct 
			var_name = extract_var_name(args[i]); //protect 
			if (!is_in_env(data->env, var_name))
				add_env_var(&data->env, args[i]); //protect 
			else
				set_env_var(&data->env, var_name, args[i]); //protect and free
			free(var_name);
		}
		//else
			//mark for subshell
		i++;
	}
	return (EXIT_SUCCESS);
}