#include "minishell.h"

static char	*copy_spe_char(char *input, size_t start, size_t *end, size_t len)
{
	char	*str;
	size_t	i;

	str = malloc(len + 1);
	if (!str)
		return (NULL);

	i = 0;
	while (start < (*end))
		str[i++] = input[start++];
	str[i] = '\0';
	
	return (str);
}
char	*extract_spe_char(char *input, size_t *i)
{
	char	*str;
	size_t 	start;
	size_t 	len;
	
	start = (*i);
	len = get_spe_char_len(input, i);
	str = copy_spe_char(input, start, i, len);
	return (str);
}