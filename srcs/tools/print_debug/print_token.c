/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:27:10 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/07 08:39:47 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_tok *token)
{
    t_tok *current;
	
	current = token;
	
	printf("PRINT_TEST:\n");
    while (current)
    {
        printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
        current = current->next;
    }
}