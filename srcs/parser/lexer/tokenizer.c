/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 13:58:05 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool expand_tokens(t_token *tokens) 
{
    t_token *current = tokens;

    while (current) 
	{
        t_token *next_token = current->next;

        // Si le token contient un wildcard, on applique l'expansion
        if (ft_strchr(current->str, '*'))
            expand_from_wc(&current);

        current = next_token;
    }
    return true;
}

bool tokenizer(t_data *data, char *input, bool need_expand) 
{
    t_tok_type token;
    size_t input_len = ft_strlen(input);
    size_t i = 0;

    if (input_len <= 0)
        return EXIT_FAILURE;

    // Boucle de tokenisation
    while (i < input_len) 
	{    
        token = 0;
        if (str_handler(data, input, &token, &i))
            return EXIT_FAILURE;
        if (special_char_handler(data, input, &token, &i, need_expand)) // Gère les caractères spéciaux
            return EXIT_FAILURE;
    }

    // Expansion des wildcards
    if (!expand_tokens(data->token))  // Ajoute cette ligne
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
