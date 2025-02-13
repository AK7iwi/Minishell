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
	T_D_REDIR_OUT,
	T_REDIR_IN,
	T_HEREDOC,
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

typedef struct s_op
{
	t_op_type	type;

    struct s_ast *left;
    struct s_ast *right;  
} 	t_op;

typedef struct s_subshell
{
    struct s_ast *root;
} 	t_subshell;

typedef struct s_ast
{
    t_ast_type  type;

    union
    {
        t_cmd		cmd;
        t_op		op;
        t_subshell 	subshell;
    };
} 	t_ast;

typedef struct s_tok
{
    t_tok_type type;

    char	*str;
    
    struct s_tok *prev;
    struct s_tok *next;
}   t_tok;

typedef struct s_env
{
    char	*env_var;

    struct s_env *prev;
    struct s_env *next;
}	t_env;

typedef struct s_data
{
	t_err 		err;
    t_env		*env;
    t_tok		*tok;
	t_ast 		*ast;
	t_hist		*hist;
} 	t_data;

//**********************************************//
//												//
//					  TOOLS		  				//
//												//
//**********************************************// 

/* checker.c */
bool 	is_number(char *c);
bool	ft_isdigit(int c);
bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* print_str.c */
void	ft_putstr(char *str);

/* len.c */
size_t	ft_strlen(const char *s);

/* memory.c */
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strdup(const char *s);

/////////// print ////////////////////
/* print_ast.c */
void	print_ast(t_ast *ast, int depth);
/* print_tok.c */
void 	print_token(t_tok *token);

/////////// str_manip //////////////////
/* str_manip2.c */
char	**ft_split(char const *str, char c);
/* str_manip.c */
int		ft_atoi(const char *nptr);
char	*ft_strjoin(const char *s1, const char *s2);

///////////// free /////////////////////////

/* free_ast.c */
void	free_ast(t_ast **ast);
/* free.c */
void 	free_tab(char **tab);
void	free_tokens(t_tok **tok);
void 	free_errors(t_err *err);
void	free_loop(t_data *data);
void	free_all(t_data *data);

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
/* env.c */
bool	env(t_env *env);
/* unset.c */
bool	unset(t_data *data, char **args);
/* export.c */
bool	ft_export(t_data *data, char **args);
/* pwd.c */
bool	pwd(t_err *error);
/* cd.c */
bool	cd(t_data *data, char **args);
/* echo.c */
bool	echo(char **args);

//////// builtins ///////// 
/* builtins.c */
bool	is_fork_builtins(char **args);
bool 	is_non_fork_builtins(char **args);
bool	builtins(t_data *data, char **args);

////////////////////////

/* exec_cmd_node.c */
bool	exec_cmd_node(t_data *data, t_cmd *cmd);

/* exec.c */
bool 	exec(t_data *data, t_ast *ast);

//**********************************************//
//					REDIRECTIONS		   		//
//**********************************************//

/* redirections.c */
void	    handle_redirs(t_data *data, t_cmd *cmd);

//**********************************************//
//												//
//					  PARSER		  			//
//												//
//**********************************************//

//**********************************************//
//					PARSER_TOOLS   				//
//**********************************************//

/* parse_checker3.c */
bool	    is_s_redir_out(t_tok_type type);
bool	    is_d_redir_out(t_tok_type type);
bool 	    is_redir_in(t_tok_type type);
bool 	    is_heredoc(t_tok_type type);

/* parse_checker2.c */
bool	    is_or(t_tok_type type);
bool	    is_and(t_tok_type type);
bool	    is_pipe(t_tok_type type);
bool 	    is_o_paren(t_tok_type type);
bool 	    is_c_paren(t_tok_type type);

/* parse_checker.c */
bool 	    is_paren(t_tok_type type);
bool 	    is_word(t_tok_type type);
bool 	    is_cmd(t_tok_type type);
bool	    is_redir(t_tok_type type);
bool	    is_operator(t_tok_type type);

//**********************************************//
//					AST   						//
//**********************************************//

/////// ast_node ////////////

/* operator_node.c */
t_ast		*create_operator_node(t_ast *left, t_ast *right, t_op_type op_type);
t_op_type	get_op_type(t_tok_type type);
bool        get_prec(t_tok_type type);
/*subsh_node.c */
bool		create_subsh_node(t_ast **new_node, t_tok **current);
/////// cmd_node //////////
/* handle_redirs.c */
bool		parse_redirs(t_ast **new_node, t_tok **current, size_t *i);
/* handle_args.c */
bool		parse_args(t_ast **new_node, t_tok **current, size_t *i);
/* cmd_node.c */
bool		create_cmd_node(t_ast **new_node, t_tok **current);

/* ast.c */
bool	    handle_operator(t_ast **result, t_tok **current, uint8_t min_prec);
bool	    handle_cmd_and_subsh(t_ast **ast, t_tok **current);
bool	    ast_algo(t_ast **ast, t_tok **current, uint8_t min_prec);
bool	    ast_creator(t_data *data);

//**********************************************//
//					SYN_ANALYZER   				//
//**********************************************//

/* check_op_and_redir.c */
bool		check_redir(t_err *err, t_tok *current);
bool		check_operator(t_err *err, t_tok *current);

/* check_paren.c */
bool		check_paren(t_err *err, t_tok *current, uint32_t *o, uint32_t *c);

/* syn_analyzer.c */
bool		syn_analyzer(t_data *data);

//**********************************************//
//					LEXER   					//
//**********************************************//

//////////////// lexer_tools //////////////////////
/* lexer_tools.c */
bool		is_special_char(char *input, size_t *i);
void		skip_space(char *input, size_t *i);
/* token_tools.c */
bool		add_token(t_tok **tok, t_tok_type *type, char *str);

//////////// special_char_handler ///////////////////
/* special_char_len.c */
uint8_t		get_spe_char_len(char *input, size_t *i);
/* special_char_extracter.c*/
char		*extract_spe_char(char *input, size_t *i);
/* special_char_handler.c */
bool		handle_spe_char(t_data *data, char *input, size_t *i);

//////////// str_handler ////////////////////////////
/* str_len.c */
ssize_t		get_str_len(char *input, t_tok_type *type, size_t *i);
/* str_extracter.c */
char		*extract_str(t_err *err, char *input, t_tok_type *type, size_t *i);
/* str_handler.c */
bool		handle_str(t_data *data, char *input, size_t *i);

/////////////////////////////////////////////////
/* tokenizer.c */
bool		tokenizer(t_data *data, char *input);

//**********************************************//
//												//
//					   ENV			  			//
//												//
//**********************************************// 

//////// env_tools ///////
/* env_tools2.c */
void 	    remove_env_node(t_env **env, t_env *to_remove);
bool	    is_var(char *env_var, char *var_name);
bool 	    is_in_env(t_env *env, char *var_name);
bool 	    find_equal(char *var);
bool	    is_valid_var(char *var);
/* env_tools.c */
void	    free_env(t_env **env_var);
void	    unset_env_var(t_env **env, char *var_name);
bool 	    set_env_var(t_env **env, char *var_name, char *new_env_var);
bool	    add_env_var(t_env **env, char *envp);

/* extract_env.c */
char 	    *extract_var_value(char *args);
char 	    *extract_var_name(char *args);
/* sort_env.c */
bool	    print_sorted_env(t_env *env);

/* init_env.c */
bool	    init_env(t_data *data, char **envp);

//**********************************************//
//												//
//					ERRORS       				//
//												//
//**********************************************// 

/* error_and_exit.c */
void 	    fork_error(t_data *data);
void	    pipe_error(t_data *data);
void	    open_error(t_data *data);
void	    dup2_error(t_data *data, int fd);

/* init_errors.c */
void 	    init_errors(t_data *data); 

//**********************************************//
//												//
//					INITIALIZER  				//
//												//
//**********************************************// 

/* init.c */
bool	    init(t_data *data, char **argv, char **envp);

//**********************************************//
//												//
//					SIGNALS		  				//
//												//
//**********************************************// 

/* signals.c*/
void	    signals(void);

#endif /* MINISHELL_H */