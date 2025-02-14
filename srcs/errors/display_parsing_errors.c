#include "minishell.h"

void	display_redirs_errors(uint16_t parsing_errors)
{
	ft_putstr(E_SYN);
	if (parsing_errors & ERR_S_REDIR_OUT)
		ft_putstr(E_S_REDIR_OUT);
	else if (parsing_errors & ERR_D_REDIR_OUT)
		ft_putstr(E_D_REDIR_OUT);
	else if (parsing_errors & ERR_REDIR_IN)
		ft_putstr(E_REDIR_IN);
	else if (parsing_errors & ERR_HEREDOC)
		ft_putstr(E_HEREDOC);
}

void	display_operators_errors(uint16_t parsing_errors)
{
	ft_putstr(E_SYN);
	if (parsing_errors & ERR_PIPE)
		ft_putstr(E_PIPE);
	else if (parsing_errors & ERR_AND)
		ft_putstr(E_AND);
	else if (parsing_errors & ERR_OR)
		ft_putstr(E_OR);
}

void	display_parens_errors(uint16_t parsing_errors)
{
	if (parsing_errors & ERR_G_PAREN)
		return (ft_putstr(E_G_PAREN));
	ft_putstr(E_SYN);
	if (parsing_errors & ERR_O_PAREN)
		ft_putstr(E_O_PAREN);
	else if (parsing_errors & ERR_C_PAREN)
		ft_putstr(E_C_PAREN);
}