#include "minishell.h"

void 	init_errors(t_data *data) 
{
	data->err.gen_errors = 0;
	data->err.parsing_errors = 0;
	data->err.exec_errors = 0;
}