#include "minishell.h"

inline bool is_o_paren(t_tok_type type)
{
	return (type == T_O_PAREN);
}
inline bool is_c_paren(t_tok_type type)
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