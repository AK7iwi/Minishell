/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_displayer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:49:38 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/06 14:41:12 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putstr(char *str)
{
	while (*str)
		write(STDERR_FILENO, str++, 1);
}
static void	display_exec_errors(uint16_t exec_errors)
{
	if (exec_errors & ERR_PWD)
		perror(E_PWD);
	if (exec_errors & ERR_CD1)
		ft_putstr(E_CD1);
	if (exec_errors & ERR_CD2)
		perror(E_CD2);
	if (exec_errors & ERR_UNSET)
		ft_putstr(E_UNSET);
	if (exec_errors & ERR_EXIT)
		ft_putstr(E_EXIT);
	if (exec_errors & ERR_FORK)
		perror(E_FORK);
	if (exec_errors & ERR_PIPE)
		perror(E_PIPE);
}
static void	display_parsing_errors(uint8_t parsing_errors)
{
	if (parsing_errors & ERR_QUOTE)
		ft_putstr(E_QUOTE);
	if (parsing_errors & ERR_OPERATOR)
		ft_putstr(E_OPERATOR);
	if (parsing_errors & ERR_REDIR)
		ft_putstr(E_REDIR);
	if (parsing_errors & ERR_PARAN)
		ft_putstr(E_PARAN);
}
static void	display_gen_errors(uint8_t gen_errors)
{
	if (gen_errors & ERR_MALLOC)
		ft_putstr(E_MALLOC);
	if (gen_errors & ERR_ARG)
		ft_putstr(E_ARGS);
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