/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:19:06 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/14 12:02:29 by mfeldman         ###   ########.fr       */
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
# define ERR_MALLOC			0x1
# define ERR_ARG			0x2

# define E_MALLOC			"mimishell: Insufficient system resources. Terminating program.\n"
# define E_ARGS				"mimishell: This program does not accept arguments. Usage: ./minishell\n"

/* Parsing errors */
# define ERR_QUOTE			0x1

# define ERR_PARAN			0x2
# define ERR_O_PAREN		0x4
# define ERR_C_PAREN		0x8

# define ERR_OPERATOR		0x10
# define ERR_PIPE			0x20
# define ERR_AND 			0x40
# define ERR_OR 			0x80

# define ERR_REDIR			0x100
# define ERR_S_REDIR_OUT	0X200
# define ERR_D_REDIR_OUT	0X400
# define ERR_REDIR_IN		0X800
# define ERR_HEREDOC		0X1000

# define E_SYN				"mimishell: syntax error near "

# define E_QUOTE			"mimishell: syntax error, missing closing quotation mark\n"

# define E_O_PAREN 			"`('\n"
# define E_C_PAREN 			"`)'\n"

# define E_PIPE 			"`|'\n"
# define E_AND 				"`&&'\n"
# define E_OR 				"`||'\n"

# define E_S_REDIR_OUT		"`>'\n"
# define E_D_REDIR_OUT		"`>>'\n"
# define E_REDIR_IN			"`<'\n"
# define E_HEREDOC			"`<<'\n"

/* Exec errors */
/* Builtins errors */
# define ERR_PWD			0x1
# define ERR_CD1 			0x2
# define ERR_CD2 			0x4
# define ERR_EXPORT			0x8
# define ERR_UNSET			0x10
# define ERR_EXIT			0x20

# define E_PWD 				"pwd"
# define E_CD1				"cd: too many arguments\n"
# define E_CD2				"cd"
# define E_EXPORT			"unset: not enough arguments\n"
# define E_UNSET			"unset: not enough arguments\n"
# define E_EXIT 			"bash: exit: too many arguments\n"

/* CMDS errors */
# define ERR_FORK			0x40
# define ERR_PIPE_CMD		0x80 //useless, pipe_error fct 
# define ERR_DUP2			0x100

# define E_FORK 			"fork"
# define E_PIPE_CMD			"pipe"
# define E_DUP2				"dup2"

//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_err
{
	uint8_t		gen_errors;
	uint16_t	parsing_errors; //pars_error for norme
	uint16_t	exec_errors;
}	t_err;

//**********************************************//
//												//
//					  ERRORS		  			//
//												//
//**********************************************//

/* display_parsing_errors*/
void	display_redirs_errors(uint16_t parsing_errors);
void	display_parens_errors(uint16_t parsing_errors);
void	display_operators_errors(uint16_t parsing_errors);

/* errors_displayer.c*/
void	errors_displayer(t_err error);

#endif /* ERRORS_H */