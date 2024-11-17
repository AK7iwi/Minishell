/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_displayer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:49:38 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/17 14:23:05 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_exec_errors(uint16_t exec_errors)
{
	if (exec_errors & ERR_PWD)
		perror(E_PWD);
	else if (exec_errors & ERR_CD1)
		ft_putstr(E_CD1);
	else if (exec_errors & ERR_CD2)
		perror(E_CD2);
	else if (exec_errors & ERR_UNSET)
		ft_putstr(E_UNSET);
	else if (exec_errors & ERR_EXIT)
		ft_putstr(E_EXIT);
	else if (exec_errors & ERR_FORK)
		perror(E_FORK);
	else if (exec_errors & ERR_PIPE_CMD)
		perror(E_PIPE_CMD);
}

static void	display_parsing_errors(uint16_t parsing_errors)
{
	if (parsing_errors & ERR_QUOTE)
		ft_putstr(E_QUOTE);
	if (parsing_errors & ERR_PAREN)
		display_parens_errors(parsing_errors);
	else if (parsing_errors & ERR_OPERATOR)
		display_operators_errors(parsing_errors);
	else if (parsing_errors & ERR_REDIR)
		display_redirs_errors(parsing_errors);
}
static void	display_gen_errors(uint8_t gen_errors)
{
	if (gen_errors & ERR_MALLOC)
		ft_putstr(E_MALLOC);
	else if (gen_errors & ERR_ARG)
		ft_putstr(E_ARGS);
}
void	errors_displayer(t_err error)
{
	if (error.gen_errors)
		display_gen_errors(error.gen_errors);
	else if (error.parsing_errors)
		display_parsing_errors(error.parsing_errors);
	else if (error.exec_errors)
		display_exec_errors(error.exec_errors);
}