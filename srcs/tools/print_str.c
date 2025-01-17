#include "minishell.h"

void	ft_putstr(char *str)
{
	while (*str)
		write(STDERR_FILENO, str++, 1);
}