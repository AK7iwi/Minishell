NAME			:= minishell

SRC_DIR			:= srcs
OBJ_DIR			:= obj

SRCS			:=	main.c \
					errors/errors_displayer.c errors/errors_tools.c \
					initializer/init.c \
					env/init_env.c env/sort_env.c env/extract_env.c env/env_tools/env_tools.c env/env_tools/env_tools2.c \
					parser/lexer/tokenizer.c \
					parser/lexer/str_handler/str_handler.c parser/lexer/str_handler/str_extracter.c parser/lexer/str_handler/str_len.c \
					parser/lexer/special_char_handler/special_char_handler.c parser/lexer/special_char_handler/special_char_extracter.c parser/lexer/special_char_handler/special_char_len.c \
					parser/lexer/token_tools.c \
					parser/syn_analyzer/syn_analyzer.c parser/syn_analyzer/syn_checker.c \
					parser/ast/ast.c parser/ast/ast_printer.c parser/ast/ast_freer.c \
					parser/ast/ast_node/cmd_node.c parser/ast/ast_node/operator_node.c parser/ast/ast_node/subsh_node.c \
					parser/parser_tools/parser_checker.c parser/parser_tools/parser_checker2.c \
					exec/exec.c \
					exec/builtins/builtins.c \
					exec/builtins/builtins_cmds/echo.c exec/builtins/builtins_cmds/pwd.c exec/builtins/builtins_cmds/env.c \
					exec/builtins/builtins_cmds/cd.c  exec/builtins/builtins_cmds/unset.c exec/builtins/builtins_cmds/export.c \
				 	exec/builtins/builtins_cmds/history.c exec/builtins/builtins_cmds/exit.c \
					exec/cmds/cmds.c \
					exec/pipe/pipe.c \
					tools/lib/lib_checker.c tools/lib/lib_len.c tools/lib/lib_memory.c \
					tools/lib/lib_str_manip/lib_str_manip.c tools/lib/lib_str_manip/lib_str_manip2.c \
					tools/free/free.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
CPPFLAGS    	:= -I includes
FSANITIZE_FLAG	:= -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -fstack-protector-strong -fno-optimize-sibling-calls 

RM				:= rm -rf
DIR_DUP     	= mkdir -p $(@D)

# Color
DEF_COLOR	= \033[0;39m
RED 		= \033[0;36m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS)  -lreadline -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)
	@echo "$(RED)Minishell objects cleaned!$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)Minishell cleaned!$(DEF_COLOR)"

re:	fclean all
	@echo "$(RED)Cleaned and rebuilt!$(DEF_COLOR)"

.PHONY: all clean fclean re