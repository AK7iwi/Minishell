/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:13:08 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/13 20:12:54 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool	is_s_redir_out(t_tok_type type)
{
	return (type == T_S_REDIR_OUT);
}

inline bool	is_d_redir_out(t_tok_type type)
{
	return (type == T_D_REDIR_OUT);
}
inline bool is_redin_in(t_tok_type type)
{
	return (type == T_S_REDIR_IN);
}

inline bool is_heredoc(t_tok_type type)
{
	return (type == T_HERE_DOC);
}
