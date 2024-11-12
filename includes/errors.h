/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:19:06 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/12 09:56:44 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

//**********************************************//
//					INCLUDES					//
//**********************************************//

#include <stdint.h>

//**********************************************//
//					DEFINES						//
//**********************************************//

/* Colors */
# define COLOR_RESET   "\x1b[0m"
# define COLOR_RED     "\x1b[31m"

/* General errors */
# define ERR_MALLOC		0x1
# define ERR_ARG		0x2

# define E_MALLOC		"mimishell: Insufficient system resources. Terminating program.\n"
# define E_ARGS			"mimishell: This program does not accept arguments. Usage: ./minishell\n"

/* Parsing errors */
# define ERR_QUOTE		0x1
# define ERR_OPERATOR	0x2
# define ERR_REDIR		0x4
# define ERR_PARAN		0x8

# define E_QUOTE		"Syntax Error: Missing closing quotation mark.\n"
# define E_OPERATOR 	"Invalid use of operator.\n"
# define E_REDIR 		"Invalid use of redirection.\n"
# define E_PARAN 		"Close the paranthese bro.\n"

/* Exec errors */

/* Builtins errors */
# define ERR_PWD		0x1
# define ERR_CD1 		0x2
# define ERR_CD2 		0x4
# define ERR_EXPORT		0x8
# define ERR_UNSET		0x10
# define ERR_EXIT		0x20

# define E_PWD 			"pwd"
# define E_CD1			"cd: too many arguments\n"
# define E_CD2			"cd"
# define E_EXPORT		"unset: not enough arguments\n"
# define E_UNSET		"unset: not enough arguments\n"
# define E_EXIT 		"bash: exit: too many arguments\n"

/* CMDS errors */

# define ERR_FORK		0x40
# define ERR_PIPE		0x80
# define ERR_DUP2		0x100

# define E_FORK 		"fork"
# define E_PIPE			"pipe"
# define E_DUP2			"dup2"

//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_err
{
	uint8_t		gen_errors;
	uint8_t		parsing_errors; //pars_error for norme
	uint16_t	exec_errors;
}	t_err;

//**********************************************//
//												//
//					  ERRORS		  			//
//												//
//**********************************************//

/* errors_displayer.c*/
void	errors_displayer(t_err error);

#endif /* ERRORS_H */