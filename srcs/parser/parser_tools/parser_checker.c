/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:17:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/20 16:28:53 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool is_cmd(t_tok_type type)
{
	return (!is_operator(type) 
		&& !is_closed_paren(type) 
		&& !is_open_paren(type)
		&& !is_redir(type));
}
inline bool is_redir(t_tok_type type)
{
	return (type == TOKEN_SIMPLE_REDIRECT_OUT 
		|| type == TOKEN_DOUBLE_REDIRECT_OUT
		|| type == TOKEN_SIMPLE_REDIRECT_IN
		|| type == TOKEN_HERE_DOC);
}
inline bool is_operator(t_tok_type type)
{
	return ((is_pipe(type) 
		|| is_and(type) 
		|| is_or(type)));
}