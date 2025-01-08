#include "minishell.h"

static	t_tok_type	get_spe_char_type(char *spe_char)
{
    if (spe_char[0] == '|' && !spe_char[1])
        return (T_PIPE);
    else if (spe_char[0] == '<' && !spe_char[1])
        return (T_REDIR_IN);
    else if (spe_char[0] == '>' && !spe_char[1])
        return (T_S_REDIR_OUT);
    else if (spe_char[0] == '<' && spe_char[1] == '<' && !spe_char[2])
        return (T_HEREDOC);
    else if (spe_char[0] == '>' && spe_char[1] == '>' && !spe_char[2])
        return (T_D_REDIR_OUT);
    else if (spe_char[0] == '&' && spe_char[1] == '&' && !spe_char[2])
        return (T_AND);
    else if (spe_char[0] == '|' && spe_char[1] == '|' && !spe_char[2])
        return (T_OR);
    else if (spe_char[0] == '(' && !spe_char[1])
        return (T_O_PAREN);
    else if (spe_char[0] == ')' && !spe_char[1])
        return (T_C_PAREN);

    return (T_WORD);
}

bool	handle_spe_char(t_data *data, char *input, size_t *i)
{
	t_tok_type	type;
	char 		*spe_char; 
	
	spe_char = extract_spe_char(input, i);
	if (!spe_char)
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	
	type = get_spe_char_type(spe_char);
	if (add_token(&data->tok, &type, spe_char))
	{
		free(spe_char);	
		return (data->err.gen_errors |= ERR_MALLOC, EXIT_FAILURE);
	}
	
	free(spe_char);
	return (EXIT_SUCCESS);
}