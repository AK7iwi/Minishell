/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:55:21 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/17 16:56:34 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extract_var_value(char *args)
{
	char *var_value;
	size_t len;
	size_t i;
	size_t j;

	i = 0;
	while (args[i] != '=')
		i++;
	i++;
	len = 0;
	while (args[i + len])
		len++;

	var_value = malloc(len + 1);
	if (!var_value)
		return (NULL);

	j = 0;
	while (j < len)
	{
		var_value[j] = args[i + j];
		j++;
	}
	var_value[j] = '\0';
	return (var_value);
}
char *extract_var_name(char *args)
{
	char *var_name;
	size_t len;
	size_t i;
	
	len = 0;
	while (args[len] != '=')
		len++;
	
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);

	i = 0;
	while (i < len)
	{
		var_name[i] = args[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}
