#ifndef MINISHELL_H
# define MINISHELL_H

//**********************************************//
//					INCLUDES					//
//**********************************************//

#include "errors.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>

//**********************************************//
//					DEFINES						//
//**********************************************//

#define TOKEN_WORD                  1
#define TOKEN_PIPE                  2  // |
#define TOKEN_SIMPLE_REDIRECT_IN    3  // <
#define TOKEN_SIMPLE_REDIRECT_OUT   4  // >
#define TOKEN_DOUBLE_REDIRECT_IN    5  // << (here_doc)
#define TOKEN_DOUBLE_REDIRECT_OUT   6  // >>
#define TOKEN_ENV_VAR         		7  // $
#define TOKEN_AND                   8 // &&
#define TOKEN_OR                    9 // ||
#define TOKEN_OPEN_PAREN            10 // (
#define TOKEN_CLOSE_PAREN           11 // )

//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_env_list
{
    char *str;
    struct s_env_list *prev;
    struct s_env_list *next;
}	t_env_list;

typedef struct s_cmd
{
    struct s_cmd *prev;
    struct s_cmd *next;
}	t_cmd;

typedef struct s_token
{
    char *str;
    uint8_t type;
    
    struct s_token *prev;
    struct s_token *next;
}   t_token;

typedef struct s_data
{
	t_error 	error;
    t_token		*token;
    t_cmd 		*cmd;
    t_env_list	*env;
} 	t_data;

//**********************************************//
//					Parser   					//
//**********************************************//

/* parse_token.c */

bool parse_tokens(t_token **tokens);

//**********************************************//
//					LEXER    					//
//**********************************************//

/* str_len.c */
bool	handle_quotes_len(char *input, ssize_t *str_len, uint8_t *t, size_t *i);
ssize_t handle_str_len(char *input, uint8_t *token, size_t *i);

/* handle_str.c */
char*	extract_str(char *input, uint8_t *token, size_t *index);

/* token.c */
bool	tokenisation(char *input, t_token **tokens);

//**********************************************//
//					MAIN    					//
//**********************************************//

// /* env_utils.c */
// void free_env_list(t_env_list **lst);
// char *get_env_value(char *var, t_env_list *env);
// char *extract_var_name(char *str, int *i);
// char *replace_env_vars(char *line, t_env_list *env);
// void replace_dollars_in_command(char **line, t_env_list *env);
// void append_env_list(t_env_list **lst, char *str);
// t_env_list *create_env_list(char **envp);

//**********************************************//
//					UTILS   					//
//**********************************************//

/* msg_error.c*/
void	msg_error(t_error error);

/* free.c */
void	free_token(t_token **tokens);
void	free_all(t_data *data);

/* Libft */

/* lib_checker.c */
int		ft_isalnum(int c);
bool    is_space(char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/* lib_len.c */
size_t	ft_strlen(const char *s);
/* lib_memory.c */
char	*ft_strdup(const char *s);
/* lib_str_manip.c */
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif /* MINISHELL_H */