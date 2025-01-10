#include "minishell.h"

void	print_token(t_tok *token)
{
    t_tok *current;
	
	current = token;
	
	printf("PRINT_TEST:\n");
    while (current)
    {
        printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
        current = current->next;
    }
}