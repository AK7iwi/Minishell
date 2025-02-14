#include "minishell.h"

bool	env(t_env *env)
{
	t_env *current;
		
	current = env;
	while (current)
	{
		printf("%s\n", current->env_var);
		current = current->next;
	}

	return (EXIT_SUCCESS);
}
