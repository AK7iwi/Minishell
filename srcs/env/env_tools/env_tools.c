#include "minishell.h"

void	free_env(t_env **env_var)
{
    t_env	*tmp;

    while (*env_var)
    {
        tmp = (*env_var)->next;
        free((*env_var)->env_var);
        free(*env_var);
        *env_var = tmp;
    }
}

void	unset_env_var(t_env **env, char *var)
{
    t_env *current;

	current = *env;
    while (current)
    {
        if (is_var(current->env_var, var))
            return (remove_env_node(env, current));
        current = current->next;
    }
}

bool	set_env_var(t_env **env, char *var_name, char *new_env_var)
{
	t_env *current;

	current = *env;
	while (current)
	{
		if (is_var(current->env_var, var_name))
		{
			free(current->env_var);
			current->env_var = ft_strdup(new_env_var);
			if (!current->env_var)
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	
	return (EXIT_SUCCESS);
}

bool	add_env_var(t_env **env, char *envp)
{
    t_env *new_env_var;
    t_env *last;
	
	new_env_var = malloc(sizeof(t_env));
    if (!new_env_var)
		return (EXIT_FAILURE);

	new_env_var->env_var = ft_strdup(envp);
	if (!new_env_var->env_var)
		return (free(new_env_var), EXIT_FAILURE);
    new_env_var->next = NULL;
	
    if (*env == NULL) 
    {
        new_env_var->prev = NULL;
        *env = new_env_var;
        return (EXIT_SUCCESS);
    }
	last = *env;
    while (last->next)
        last = last->next;
    last->next = new_env_var;
    new_env_var->prev = last;

	return (EXIT_SUCCESS);
}
