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

/* Tokens */

#define TOKEN_WORD                  1
#define TOKEN_PIPE                  2  // |
#define TOKEN_SIMPLE_REDIRECT_IN    3  // <
#define TOKEN_SIMPLE_REDIRECT_OUT   4  // >
#define TOKEN_HERE_DOC              5  // << (here_doc)
#define TOKEN_DOUBLE_REDIRECT_OUT   6  // >>
#define TOKEN_ENV_VAR         		7  // $
#define TOKEN_AND                   8 // &&
#define TOKEN_OR                    9 // ||
#define TOKEN_OPEN_PAREN            10 // (
#define TOKEN_CLOSE_PAREN           11 // )

/* Special characters */

#define SPACE 						' '
#define NULL_CHAR					'\0'
#define S_QUOTE						'\''
#define D_QUOTE						'\"'

//**********************************************//
//					ENUM						//
//**********************************************//

typedef enum e_ast_type
{
    AST_COMMAND,
    AST_OPERATOR,
	AST_SUBSH,
}	t_ast_type;

typedef enum e_op_type
{
    AST_PIPE,
	AST_AND,
	AST_OR,
}	t_op_type;

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
	char **args;
	// char **i_files;
	// char **o_files;

}	t_cmd;

typedef struct s_operator
{
	t_op_type	type;

    struct s_ast *left;
    struct s_ast *right;  
} 	t_operator;

typedef struct s_subshell
{
    struct s_ast *root;
} 	t_subshell;

typedef struct s_ast
{
    t_ast_type  type;

    union
    {
        t_cmd      cmd;
        t_operator operator;
        t_subshell subshell;
    };
} 	t_ast;

typedef struct s_token
{
    char	*str;
    uint8_t type;
    
    struct s_token *prev;
    struct s_token *next;
}   t_token;

typedef struct s_data
{
	t_error 	error;
    t_token		*token;
	t_ast 		*ast;
    t_env_list	*env;
} 	t_data;

//**********************************************//
//					AST   						//
//**********************************************//

/* ast_free.c */
void 	free_ast(t_ast **ast);

/* ast_print.c */
void 	print_ast(t_ast *ast, int depth);

/* ast_utils.c */
bool 	is_arg_cmd(uint8_t type);

/* operator_node.c */
t_ast	*create_operator_node(t_ast *left, t_ast *right, t_op_type op_type);

/* cmd_node.c */
t_ast	*create_node_cmd(t_token **current);

/*subsh_node.c */
t_ast	*create_subsh_node(t_token **current);

/* ast.c */
t_ast	*ast_algo(t_token **current, int min_prec);
void 	create_ast(t_data *data);

//**********************************************//
//					PARSER   					//
//**********************************************//

/* synthesis_analysis_utils.c */
bool	is_redir(uint8_t type);
bool	is_operator(uint8_t type);

/* synthesis_analysis_utils2.c */
bool	is_or(uint8_t type);
bool	is_and(uint8_t type);
bool	is_pipe(uint8_t type);
bool 	is_open_paren(uint8_t type);
bool 	is_closed_paren(uint8_t type);

/* synthax_error.c */
bool	check_paren(t_token *current, uint32_t *o_counter, uint32_t *c_counter);
bool 	check_redir(t_token *current);
bool 	check_operator(t_token *current);

/* analyze_token.c */
bool	analyze_tokens(t_data *data);

//**********************************************//
//					LEXER    					//
//**********************************************//

//////////// Handle special character ///////////////////

/* special_char_len.c */
uint8_t get_special_char_len(char *input, size_t *i);

/* extract_special_char.c*/
char*	extract_special_char(t_error *error, char *input, size_t *i);

/* handle_special_char.c */
bool	is_special_char(char *input, size_t *i);
bool 	handle_special_char(t_data *data, char *input, uint8_t *token, size_t *index);

//////////// Handle str ///////////////////

/* str_len.c */
bool	get_quotes_len(char *input, ssize_t *str_len, uint8_t *t, size_t *i);
ssize_t	get_str_len(char *input, uint8_t *token, size_t *i);

/* extract_str.c */
char*	extract_str(t_error *error, char *input, uint8_t *token, size_t *index);

/* handle_str.c */
bool 	handle_str(t_data *data, char *input, uint8_t *token, size_t *index);

/* token_utils.c */
bool	add_token(t_token **token_struct, uint8_t *token, char *str_token);
uint8_t wich_token(char *str);

/* token.c */
bool	tokeniser(t_data *data, char *input);

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

/* free.c */
void	free_loop(t_data *data);
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