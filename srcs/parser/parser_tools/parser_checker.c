#include "minishell.h"

inline 	bool 	is_paren(t_tok_type type)
{
	return (is_o_paren(type) || is_c_paren(type));
}

inline  bool 	is_word(t_tok_type type)
{
	return (type == T_WORD || type == T_ENV_VAR);
}

inline	bool	is_cmd(t_tok_type type)
{
	return (!is_operator(type) 
			&& !is_c_paren(type) 
			&& !is_o_paren(type));
}
inline	bool	is_redir(t_tok_type type)
{
	return (is_s_redir_out(type) 
			|| is_d_redir_out(type)
			|| is_redir_in(type)
			|| is_heredoc(type));
}
inline	bool	is_operator(t_tok_type type)
{
	return ((is_pipe(type) 
			|| is_and(type) 
			|| is_or(type)));
}