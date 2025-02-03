#include "minishell.h"

static size_t get_args_len(t_tok *current, size_t *i)
{
	size_t args_len;

	args_len = 0;
    while (current && is_word(current->type))
    {
        args_len++;
		(*i)++;
        current = current->next;
    } 
	return (args_len);
}

static	char **copy_args(t_ast **new_node, t_tok **current, size_t *i)
{
	char **args;
	size_t j;

	(*new_node)->cmd.args_count = get_args_len((*current), i);
	args = malloc(((*new_node)->cmd.args_count + 1) * sizeof(char *));
	// args= NULL;
	if (!args)
        return (NULL);
	
	j = 0;
	while (j < (*new_node)->cmd.args_count)
	{
		//test
		// if (j != 1)
		args[j] = ft_strdup((*current)->str);
		// else
			// args[j] = NULL;

		if (!args[j])
		{
			printf("args[j]\n");
			return (free_tab(args), NULL);
		}
		(*current) = (*current)->next;
		j++;
	}
	args[j] = NULL;
	return (args);
}

bool	parse_args(t_ast **new_node, t_tok **current, size_t *i)
{
	char **args;

	args = copy_args(new_node, current, i);
	if (!args)
	{
		printf("copy_args\n");
		return (EXIT_FAILURE);
	}
	
	if ((*new_node)->cmd.args_count)
		(*new_node)->cmd.args = args;
	else
		free_tab(args);
	
	return (EXIT_SUCCESS);
}
