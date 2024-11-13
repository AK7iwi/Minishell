/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:17:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/13 20:38:18 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline  bool 	is_word(t_tok_type type)
{
	return (type == T_WORD || type == T_ENV_VAR);
}

inline	bool	is_cmd(t_tok_type type)
{
	return (!is_operator(type) 
			&& !is_closed_paren(type) 
			&& !is_open_paren(type));
}
inline	bool	is_redir(t_tok_type type)
{
	return (is_s_redir_out(type) 
			|| is_d_redir_out(type)
			|| is_redin_in(type)
			|| is_heredoc(type));
}
inline	bool	is_operator(t_tok_type type)
{
	return ((is_pipe(type) 
			|| is_and(type) 
			|| is_or(type)));
}