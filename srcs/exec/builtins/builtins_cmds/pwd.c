#include "minishell.h"

bool	pwd(t_err *error)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	// cwd = NULL;
	if (!cwd)
		return (error->exec_errors |= ERR_PWD, EXIT_FAILURE);
	else
		printf("%s\n", cwd);

	free(cwd);
	return (EXIT_SUCCESS);
}