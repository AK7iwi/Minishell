/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:06:25 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/11 11:06:28 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_number(char *c)
{
	size_t i;

	i = 0;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (false);
		i++;
	}

	return (true);
}
inline bool	ft_isalnum(int c)
{   
	return (ft_isalpha(c) || ft_isdigit(c));
}
inline	bool	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

inline bool	ft_isalpha(int c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}