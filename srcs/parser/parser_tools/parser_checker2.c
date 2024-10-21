/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:40:57 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/21 08:08:51 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool is_open_paren(t_tok_type type)
{
	return (type == T_O_PAREN);
}
inline bool is_closed_paren(t_tok_type type)
{
	return (type == T_C_PAREN);
}
inline bool is_or(t_tok_type type)
{
	return (type == T_OR);
}

inline bool is_and(t_tok_type type)
{
	return (type == T_AND);	
}
inline bool is_pipe(t_tok_type type)
{
	return (type == T_PIPE);
}