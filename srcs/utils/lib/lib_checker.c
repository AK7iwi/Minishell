#include "minishell.h"

int	ft_isalnum(int c)
{   //one return 
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
