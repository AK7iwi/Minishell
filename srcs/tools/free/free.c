#include "minishell.h"

void free_tab(char **tab)
{
    size_t i;
	
	i = 0;
    while (tab[i])
    {
		printf("free:%s\n", tab[i]);
        free(tab[i]);
        i++;
    }
    free(tab);
}

void	free_tokens(t_tok **tok)
{
	t_tok	*tmp;
	t_tok	*current;

	if (!(*tok))
		return ;
	current = *tok;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
	}
	*tok = NULL;
}

void 	free_errors(t_err *err)
{
	err->gen_errors = 0;
	err->parsing_errors = 0;
	err->exec_errors = 0;
}

void	free_loop(t_data *data)
{
	if (data->err.gen_errors || data->err.parsing_errors || data->err.exec_errors)
		free_errors(&data->err);
	if (data->tok)
		free_tokens(&data->tok);
	if (data->ast)
		free_ast(&data->ast);
}

void	free_all(t_data *data)
{
	free_loop(data);
	if (data->env)
		free_env(&data->env);
	
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}