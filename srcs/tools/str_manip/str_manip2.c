/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manip2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:09:52 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/06 15:28:49 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_charset(char const str, char c)
{
	if (str == c)
		return (1);
	return (0);
}

static int	ft_is_word(char const *str, char c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	if (str[i] == 0)
		return (0);
	while (str[i])
	{
		while (ft_is_charset(str[i], c) && str[i])
			i++;
		if (!ft_is_charset(str[i], c) && str[i])
		{
			while (!ft_is_charset(str[i], c) && str[i])
				i++;
			word++;
		}
	}
	return (word);
}

static char	**ft_malloc_word(char const *str, char c, char **dest, int word)
{
	int		i;
	int		j;
	int		letter;

	i = 0;
	j = 0;
	while (str[i])
	{
		letter = 0;
		while (ft_is_charset(str[i], c) && str[i])
			i++;
		while (!ft_is_charset(str[i], c) && str[i])
		{
				letter++;
				i++;
		}
		if (j < word)
		{
			dest[j] = malloc((sizeof(char) * letter) + 1);
			if (!dest[j++])
				return (NULL);
		}
	}
	return (dest);
}

static char	**ft_put_word(char const *str, char c, char **dest)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (str[i])
	{
		j = 0;
		while (ft_is_charset(str[i], c) && str[i])
			i++;
		if (!ft_is_charset(str[i], c) && str[i])
		{
			while (!ft_is_charset(str[i], c) && str[i])
				dest[k][j++] = str[i++];
			dest[k][j] = '\0';
			k++;
		}
	}
	return (dest);
}

char	**ft_split(char const *str, char c)
{
	char	**dest;
	int		word;

	word = ft_is_word(str, c);
	dest = malloc(sizeof(char *) * (word + 1));
	if (!dest)
		return (NULL);
	dest = ft_malloc_word(str, c, dest, word);
	if (!dest)
		return (NULL);
	dest = ft_put_word(str, c, dest);
	dest[word] = 0;
	return (dest);
}