#include "minishell.h"

void	remove_env_node(t_env **env, t_env *to_remove)
{
    if (to_remove->prev)
        to_remove->prev->next = to_remove->next;
    if (to_remove->next)
        to_remove->next->prev = to_remove->prev;

    if (to_remove == *env)
        *env = to_remove->next;

    free(to_remove->env_var);
    free(to_remove);
}

bool	is_var(t_env *current, char *var_name)
{
	return (ft_strncmp(current->env_var, var_name, ft_strlen(var_name)) == 0
			&& ((current->env_var[ft_strlen(var_name)] == '='
			|| current->env_var[ft_strlen(var_name)] == '\0')));
}

bool 	is_in_env(t_env *env, char *var_name)
{
	t_env *current;

	current = env;
	while (current)
	{
		if (is_var(current, var_name))
			return (true);
		current = current->next;
	}
	
	return (false);
}

bool find_equal(char *var)
{
	size_t i;

	i = 0;

	while (var[i])
	{
		if (var[i] == '=')
			return (true);
		i++;
	}
	
	return (false);
}

bool	is_valid_var(char *var)
{
	size_t i; 
	
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (false);
	
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	
	return (true);
}