/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:17:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/23 10:33:36 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool is_cmd(t_tok_type type)
{
	return (!is_operator(type) 
		&& !is_closed_paren(type) 
		&& !is_open_paren(type));
}
inline bool is_redir(t_tok_type type)
{
	return (type == T_S_REDIR_OUT 
		|| type == T_D_REDIR_OUT
		|| type == T_S_REDIR_IN
		|| type == T_HERE_DOC);
}
inline bool is_operator(t_tok_type type)
{
	return ((is_pipe(type) 
		|| is_and(type) 
		|| is_or(type)));
}