/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_displayer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:49:38 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/16 10:58:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putstr(char *str, int fd)
{
	if (fd < 0)
		return ; //protect 
	while (*str)
		write(fd, str++, 1);
}
static void	display_exec_errors(uint16_t exec_errors)
{
	if (exec_errors & ERROR_PWD)
		perror(E_PWD);
	if (exec_errors & ERROR_CD1)
		ft_putstr(E_CD1, 2);
	if (exec_errors & ERROR_CD2)
		perror(E_CD2);
	if (exec_errors & ERROR_UNSET)
		ft_putstr(E_UNSET, 2);
	if (exec_errors & ERROR_EXIT)
		ft_putstr(E_EXIT, 2);
	if (exec_errors & ERROR_EXECVE)
		perror(E_EXECVE);
	if (exec_errors & ERROR_FORK)
		perror(E_FORK);
}
static void	display_parsing_errors(uint8_t parsing_errors)
{
	if (parsing_errors & ERROR_QUOTE)
		ft_putstr(E_QUOTE, 2);
	if (parsing_errors & ERROR_OPERATOR)
		ft_putstr(E_OPERATOR, 2);
	if (parsing_errors & ERROR_REDIR)
		ft_putstr(E_REDIR, 2);
	if (parsing_errors & ERROR_PARAN)
		ft_putstr(E_PARAN, 2);
}
static void	display_gen_errors(uint8_t gen_errors)
{
	if (gen_errors & ERROR_MALLOC)
		ft_putstr(E_MALLOC, 2);
	if (gen_errors & ERROR_ARG)
		ft_putstr(E_ARGS, 2);
}
void	errors_displayer(t_error error)
{
	if (error.gen_errors)
		display_gen_errors(error.gen_errors);
	else if (error.parsing_errors)
		display_parsing_errors(error.parsing_errors);
	else if (error.exec_errors)
		display_exec_errors(error.exec_errors);
}