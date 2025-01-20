#include "minishell.h"

static void	sort_env(t_env **env)
{
	bool swapped;
    t_env *current;
	char *temp;
	
	swapped = true;
    while (swapped)
    {
        swapped = false;
        current = *env;

        while (current->next)
        {
            if (strcmp(current->env_var, current->next->env_var) > 0) //ft_strcmp
            {
				temp = current->env_var;
    			current->env_var = current->next->env_var;
    			current->next->env_var = temp;
                swapped = true;
            }
            current = current->next;
        }
    }
}
bool	print_sorted_env(t_env *env)
{
	t_env *current;
	current = env;
	char *var_name;
	char *var_value;
	
	sort_env(&current);
	
	while (current)
	{
		var_name = extract_var_name(current->env_var);
		var_value = extract_var_value(current->env_var);
		printf("export %s=\"%s\"\n", var_name, var_value);
		free(var_name);
		free(var_value);
		current = current->next;
	}
	
	return (EXIT_SUCCESS);
}