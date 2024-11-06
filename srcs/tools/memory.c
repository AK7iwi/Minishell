/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:06:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/06 16:25:13 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
	
	i = 0;
    while (i < n && src[i] != '\0')
	{
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return (dest);
}
char	*ft_strdup(const char *str)
{
	char	*tab;
	int		len;

	if (!str)
		return (NULL);

	len = 0;
	while (str[len])
		len++;
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	tab = ft_strncpy(tab, str, len + 1);
	return (tab);
}