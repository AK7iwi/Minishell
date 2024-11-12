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

char *get_env_value(const char *var_name, t_env *env_list)
{
    int var_len = ft_strlen(var_name);

    while (env_list) 
    {
        if (ft_strncmp(env_list->str, var_name, var_len) == 0 && env_list->str[var_len] == '=') 
            return env_list->str + var_len + 1;
        env_list = env_list->next;
    }
    return NULL;
}

int handle_env_variable(const char *input, int *i, char *output, int *j, t_env *env_list) 
{
    char var_name[256];
    int start = *i, var_len = 0; (void)start;

    while (input[*i] && ((input[*i] >= 'a' && input[*i] <= 'z') || (input[*i] >= 'A' && input[*i] <= 'Z') || input[*i] == '_')) 
    {
        var_name[var_len++] = input[*i];
        (*i)++;
    }
    var_name[var_len] = '\0'; 

    char *env_value = get_env_value(var_name, env_list);
    if (env_value)
    {
        ft_strcpy(output + (*j), env_value);
        (*j) += ft_strlen(env_value);
    }
    return 1;
}

char *expand_variable(const char *input, t_env *env_list, bool expand)
 {
    char *output = malloc(1024);  
    int i = 0, j = 0;
    while (input[i]) 
    {
        if (input[i] == '$' && !expand) 
        {
            i++; 

            if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || input[i] == '_')
                handle_env_variable(input, &i, output, &j, env_list);
        } 
        else 
            output[j++] = input[i++]; 
    }

    output[j] = '\0';
    return output;
}