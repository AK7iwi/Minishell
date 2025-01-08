#include "minishell.h"

static inline bool is_arg(t_err *error, int argc)
{
	return ((argc != 1) && (error->gen_errors |= ERR_ARG));
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;
	
	signals(); 
	if (init(&data, argv, envp) || is_arg(&data.err, argc))
		return (errors_displayer(data.err), free_all(&data), EXIT_FAILURE);
	
    while (true)
    {
        input = readline("mimishell<> ");
		if (!input)
			return (printf("exit\n"), free_all(&data), EXIT_FAILURE); //ft_exit
		add_history(input);
		
        if (tokenizer(&data, input) || syn_analyzer(&data)
				|| ast_creator(&data) || exec(&data, data.ast))
			errors_displayer(data.err);
	
		free_loop(&data);
    }
    return (EXIT_SUCCESS);
}