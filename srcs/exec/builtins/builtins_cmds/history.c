/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:07:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 09:51:21 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool check_c_flag(char **args)
{
	bool c_flag;
	size_t i;
	
	c_flag = false;
	i = 1;
	
    while (args[i] && args[i][0] == '-' && args[i][1] == 'c') 
    {
        size_t j;
		j = 2;
		
        while (args[i][j] && args[i][j] == 'c')
            j++;
		
		if (args[i][j] == '\0')
        	c_flag = true;
		else
			break;
        (i)++;
    }

    return (c_flag);
	
}
bool	history(char **args)
{
	bool clear;
	
	clear = check_c_flag(args);
	if (clear)
        rl_clear_history();
	// else 
    // {
    //     // display_history();
    // }

	return (EXIT_SUCCESS);
}