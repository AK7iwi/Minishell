/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:51:40 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 14:28:36 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char *get_env_value(const char *var_name, t_env *env_list)
{
    int var_len;

    var_len = ft_strlen(var_name);
    while (env_list) 
    {
        if (ft_strncmp(env_list->str, var_name, var_len) == 0 &&
            env_list->str[var_len] == '=') 
            return env_list->str + var_len + 1;
        env_list = env_list->next;
    }
    return NULL;
}

int handle_env_variable(const char *input, int *i, char *output, int *j, t_env *env_list) 
{
    int start; 
    int var_len;
    char *var_name;

    var_len = 0;
    start = *i;
    while (input[*i] && ((input[*i] >= 'a' && input[*i] <= 'z') ||
        (input[*i] >= 'A' && input[*i] <= 'Z') || input[*i] == '_')) 
    {
        (*i)++;
        var_len++;
    }
    var_name = malloc(var_len + 1);
    if (!var_name)
        return 0;
    ft_strncpy(var_name, &input[start], var_len);
    var_name[var_len] = '\0';
    char *env_value;
    env_value = get_env_value(var_name, env_list);
    if (env_value)
    {
        ft_strcpy(output + (*j), env_value);
        (*j) += ft_strlen(env_value);
    }
    free(var_name);
    return 1;
}

static char *get_var_length_and_value(const char *input, int *i, t_env *env_list)
{
    int start;
    int var_len;
    char *var_name;
    char *env_value;

    start = *i;
    var_len = 0;
    while ((input[*i] >= 'a' && input[*i] <= 'z') ||
           (input[*i] >= 'A' && input[*i] <= 'Z') || input[*i] == '_') 
    {
        ((*i)++, var_len++);
    }
    if (var_len > 0) 
    {
        var_name = malloc(var_len + 1);
        if (!var_name)
            return NULL;
        ft_strncpy(var_name, &input[start], var_len);
        var_name[var_len] = '\0';
        env_value = get_env_value(var_name, env_list);
        free(var_name);
        return env_value;
    }
    return NULL;
}

int get_expanded_length(const char *input, t_env *env_list, bool expand)
{
    int length;
    int i;
    char *env_value;

    length = 0;
    i = 0;
    while (input[i]) 
    {
        if (input[i] == '$' && expand) 
        {
            i++;
            env_value = get_var_length_and_value(input, &i, env_list);
            if (env_value)
                length += ft_strlen(env_value);
        } 
        else 
        {
            length++;
            i++;
        }
    }
    return length;
}

char *expand_variable(const char *input, t_env *env_list, bool expand) 
{
    int output_len;
    char *output;
    int i;
    int j;

    j = 0;
    i = 0;
    output_len = get_expanded_length(input, env_list, expand);
    output = malloc(output_len + 1);
    if (!output)
        return NULL;
    while (input[i]) 
    {
        if (input[i] == '$' && expand) 
        {
            i++;
            if ((input[i] >= 'a' && input[i] <= 'z') ||
                (input[i] >= 'A' && input[i] <= 'Z') || input[i] == '_')
                handle_env_variable(input, &i, output, &j, env_list);
        } 
        else 
            output[j++] = input[i++];
    }

    output[j] = '\0';
    return output;
}
