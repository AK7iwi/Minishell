#include "minishell.h"

inline bool	is_s_redir_out(t_tok_type type)
{
	return (type == T_S_REDIR_OUT);
}

inline bool	is_d_redir_out(t_tok_type type)
{
	return (type == T_D_REDIR_OUT);
}
inline bool is_redir_in(t_tok_type type)
{
	return (type == T_REDIR_IN);
}

inline bool is_heredoc(t_tok_type type)
{
	return (type == T_HEREDOC);
}
