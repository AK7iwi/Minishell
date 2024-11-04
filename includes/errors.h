/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:19:06 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/04 10:40:54 by mfeldman         ###   ########.fr       */
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
# define ERROR_MALLOC			0x1
# define ERROR_ARG				0x2

# define E_MALLOC	"Error\nMalloc fail error.\n"
# define E_ARGS		"Error\nNo need argument bro.\n"

/* Parsing errors */
# define ERROR_QUOTE			0x1
# define ERROR_OPERATOR			0x2
# define ERROR_REDIR			0x4
# define ERROR_PARAN			0x8

# define E_QUOTE	"Error\nClose you quotes.\n"
# define E_OPERATOR "Error\nInvalid use of operator.\n"
# define E_REDIR 	"Error\nInvalid use of redirection.\n"
# define E_PARAN 	"Error\nClose the paranthese bro.\n"

/* Exec errors */

/* Builtins errors */
# define ERROR_PWD				0x1
# define ERROR_CD1 				0x2
# define ERROR_CD2 				0x4
# define ERROR_EXPORT			0x8
# define ERROR_UNSET			0x10
# define ERROR_EXIT				0x20

# define E_PWD 		"Error\npwd"
# define E_CD1		"Error\ncd: too many arguments\n"
# define E_CD2		"Error\ncd"
# define E_EXPORT	"Error\nunset: not enough arguments\n"
# define E_UNSET	"Error\nunset: not enough arguments\n"
# define E_EXIT 	"bash: exit: too many arguments\n"

/* CMDS errors */

# define ERROR_FORK				0x40
# define ERROR_PIPE				0x80
# define ERROR_DUP2				0x100

# define E_FORK 	"Error\nfork"
# define E_PIPE		"Error\npipe"
# define E_DUP2		"Error\ndup2"

/* Redirs errors */

//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_error
{
	uint8_t		gen_errors;
	uint8_t		parsing_errors; //pars_error for norme
	uint16_t	exec_errors;
}	t_error;

//**********************************************//
//												//
//					  ERRORS		  			//
//												//
//**********************************************//

/* errors_tools.c */
void 	free_errors(t_error *error);

/* errors_displayer.c*/
void	errors_displayer(t_error error);

#endif /* ERRORS_H */