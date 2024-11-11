/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:55:11 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/11 11:03:11 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(t_env **env)
{
	bool swapped;
    t_env *current;
	char *temp;
	
	swapped = true;
    while (swapped)
    {
        swapped = false;
        current = *env;

        while (current->next)
        {
            if (ft_strcmp(current->str, current->next->str) > 0) //ft_strcmp
            {
				temp = current->str;
    			current->str = current->next->str;
    			current->next->str = temp;
                swapped = true;
            }
            current = current->next;
        }
    }
}
bool	print_sorted_env(t_env *env)
{
	t_env *current;
	current = env;
	char *var_name;
	char *var_value;
	
	sort_env(&current);
	
	while (current)
	{
		var_name = extract_var_name(current->str);
		var_value = extract_var_value(current->str);
		printf("export %s=\"%s\"\n", var_name, var_value);
		free(var_name);
		free(var_value);
		current = current->next;
	}
	
	return (EXIT_SUCCESS);
}