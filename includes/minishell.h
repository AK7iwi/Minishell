#ifndef MINISHELL_H
# define MINISHELL_H

//**********************************************//
//					INCLUDES					//
//**********************************************//

#include "errors.h"
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>

//**********************************************//
//					DEFINES						//
//**********************************************//

/* Special characters */

#define SPACE 						' '
#define NULL_CHAR					'\0'
#define S_QUOTE						'\''
#define D_QUOTE						'\"'
#define ENV_VAR						'$'

//**********************************************//
//					ENUM						//
//**********************************************//

typedef enum e_op_type
{
    OP_PIPE,
	OP_AND,
	OP_OR,
}	t_op_type;

typedef enum e_ast_type
{
    AST_COMMAND,
    AST_OPERATOR,
	AST_SUBSH,
}	t_ast_type;

typedef enum e_tok_type
{
	T_WORD,
	T_PIPE,
	T_S_REDIR_OUT,
	T_D_REDIR_OUT, //APPEND
	T_S_REDIR_IN,
	T_HERE_DOC, //HEREDOC
	T_ENV_VAR,
	T_AND,
	T_OR,
	T_O_PAREN,
	T_C_PAREN,
}	t_tok_type;

//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_hist
{
    char *str;

    struct s_hist *prev;
    struct s_hist *next;
}	t_hist;

typedef struct s_env
{
    char *str;

    struct s_env *prev;
    struct s_env *next;
}	t_env;

typedef struct s_redir
{
	char 	*i_file;
    char 	*o_file;
	char 	*delim;
}	t_redir;

typedef struct s_cmd
{
	size_t 	args_count;
	size_t 	redirs_count;
	char 	**args;
	char 	**redirs;
	t_redir *redir;
}	t_cmd;

typedef struct s_operator
{
	t_op_type	type;

    struct s_ast *left;
    struct s_ast *right;  
} 	t_operator;

typedef struct s_subshell
{
    struct s_ast *root; //t_ast *root
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
    t_tok_type type;

    char	*str;
    
    struct s_token *prev;
    struct s_token *next;
}   t_token;

typedef struct s_data
{
	t_error 	error;
    t_token		*token;
	t_ast 		*ast;
    t_env		*env;
	t_hist		*hist;
} 	t_data;

//**********************************************//
//												//
//					  EXEC			  			//
//												//
//**********************************************//

//**********************************************//
//					PIPE		   				//
//**********************************************//

/* pipe.c */
bool	handle_pipe(t_data *data);

//**********************************************//
//					CMDS		   				//
//**********************************************//

/* cmds.c */
bool	cmds(t_data *data, char **args);

//**********************************************//
//					BUILTINS	   				//
//**********************************************//

/////// builtins_cmds //////////
/* exit.c */
bool	ft_exit(t_data *data, char **args);
/* history.c */
bool	history(char **args);
/* env.c */
bool	env(t_env *env);
/* unset.c */
bool	unset(t_data *data, char **args);
/* export.c */
bool	ft_export(t_data *data, char **args);
/* pwd.c */
bool	pwd(t_error *error);
/* cd.c */
bool	cd(t_data *data, char **args);
/* echo.c */
bool	echo(char **args);

//////// builtins ///////// 
/* builtins.c */
bool	is_fork_builtins(char **args);
bool 	is_non_fork_builtins(char **args);
bool	builtins(t_data *data, char **args);

/* exec.c */
bool 	exec(t_data *data, t_ast *ast);

//**********************************************//
//					REDIRECTIONS		   		//
//**********************************************//

/* redirections.c */
bool	handle_redirs(t_data *data, t_cmd *cmd);

//**********************************************//
//												//
//					  PARSER		  			//
//												//
//**********************************************//

//**********************************************//
//					PARSER_TOOLS   				//
//**********************************************//

/* parse_checker2.c */
bool	is_or(t_tok_type type);
bool	is_and(t_tok_type type);
bool	is_pipe(t_tok_type type);
bool 	is_open_paren(t_tok_type type);
bool 	is_closed_paren(t_tok_type type);

/* parse_checker.c */
bool 	is_cmd(t_tok_type type);
bool	is_redir(t_tok_type type);
bool	is_operator(t_tok_type type);

//**********************************************//
//					AST   						//
//**********************************************//

/* ast_print.c */
void 	print_ast(t_ast *ast, int depth);

/* ast_free.c */
void	free_ast(t_ast **ast); //in exec

/////// ast_node ////////////

/* operator_node.c */
t_ast	*create_operator_node(t_ast *left, t_ast *right, t_op_type op_type);
/*subsh_node.c */
t_ast	*create_subsh_node(t_ast **new_node, t_token **current);
/////// cmd_node //////////
/* handle_redirs.c */
bool	parse_redirs(t_ast **new_node, t_token **current, size_t *i);
/* handle_args.c */
bool	parse_args(t_ast **new_node, t_token **current, size_t *i);
/* cmd_node.c */
t_ast	*create_cmd_node(t_ast **new_node, t_token **current);

/* ast.c */
t_ast	*handle_cmd_and_subsh(t_token **current);
void	handle_operator(t_ast **result, t_token **current, uint8_t min_prec);
t_ast	*ast_algo(t_token **current, uint8_t min_prec);
bool	ast_creator(t_data *data);

//**********************************************//
//					SYN_ANALYZER   				//
//**********************************************//

/* syn_checker.c */
bool 	check_paren(t_token *current, uint32_t *o_counter, uint32_t *c_counter);
bool 	check_redir(t_token *current);
bool 	check_operator(t_token *current);

/* syn_analyzer.c */
bool	syn_analyzer(t_data *data);

//**********************************************//
//					LEXER   					//
//**********************************************//

/* token_tools.c */
void 		print_token(t_token *token);
void		free_token(t_token **tokens);
bool		add_token(t_token **token_struct, t_tok_type *token, char *str_token);
t_tok_type	wich_token(char *str);

//////////// special_char_handler ///////////////////

/* special_char_len.c */
uint8_t		get_special_char_len(char *input, size_t *i);
/* special_char_extracter.c*/
char*		special_char_extracter(t_error *error, char *input, size_t *i);
/* special_char_handler.c */
bool		is_special_char(char *input, size_t *i);
bool 		special_char_handler(t_data *data, char *input, t_tok_type *token, size_t *index);

//////////// str_handler ///////////////////

/* str_len.c */
bool		get_quotes_len(char *input, ssize_t *str_len, t_tok_type *t, size_t *i);
ssize_t		get_str_len(char *input, t_tok_type *token, size_t *i);
/* str_extracter.c */
char*		str_extracter(t_error *error, char *input, t_tok_type *token, size_t *index);
/* str_handler.c */
bool 		str_handler(t_data *data, char *input, t_tok_type *token, size_t *index);

//////////////////

/* tokenizer.c */
bool		tokenizer(t_data *data, char *input);

//**********************************************//
//												//
//					   ENV			  			//
//												//
//**********************************************// 

//////// env_tools ///////

/* env_tools2.c */
void 	remove_env_node(t_env **env, t_env *to_remove);
bool	is_var(t_env *current, char *var_name);
bool 	is_in_env(t_env *env, char *var_name);
bool 	find_equal(char *var);
bool	is_valid_var(char *var);

/* env_tools.c */
void	free_env(t_env **env_var);
void	unset_env_var(t_env **env, char *var_name);
bool 	set_env_var(t_env **env, char *var_name, char *new_env_var);
bool	add_env_var(t_env **env_var, char *str);

/* extract_env.c */
char 	*extract_var_value(char *args);
char 	*extract_var_name(char *args);
/* sort_env.c */
bool	print_sorted_env(t_env *env);

/* init_env.c */
bool	init_env(t_data *data, char **envp);

//**********************************************//
//												//
//					INITIALIZER  				//
//												//
//**********************************************// 

/* init.c */
bool	init(t_data *data, char **argv, char **envp);

//**********************************************//
//												//
//					  TOOLS		  				//
//												//
//**********************************************// 

/* free.c */
void 	free_tab(char **tab);
void	free_loop(t_data *data);
void	free_all(t_data *data);

//////////////// Lib ////////////////

/* lib_checker.c */
bool 	is_number(char *c);
bool	ft_isdigit(int c);
bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/* lib_memory.c */
char	*ft_strdup(const char *s);
/* lib_len.c */
size_t	ft_strlen(const char *s);

///////// lib_str_manip ///////////
/* lib_str_manip2.c */
char	**ft_split(char const *str, char c);
/* lib_str_manip.c */
int		ft_atoi(const char *nptr);
void	ft_swap(char **a, char **b);
char	*ft_strjoin(const char *s1, const char *s2);

#endif /* MINISHELL_H */