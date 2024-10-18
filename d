iuoiu
NAME			:= minishell$
$
SRC_DIR			:= srcs$
OBJ_DIR			:= obj$
$
SRCS			:= main.c \$
					parser/lexer/tokenizer.c \$
					parser/lexer/str_handler/str_handler.c \$
					parser/lexer/str_handler/str_extracter.c \$
					parser/lexer/str_handler/str_len.c \$
					parser/lexer/special_char_handler/special_char_handler.c \$
					parser/lexer/special_char_handler/special_char_extracter.c \$
					parser/lexer/special_char_handler/special_char_len.c \$
					parser/lexer/token_utils.c \$
					parser/syn_analyzer/syn_analyzer.c \$
					parser/syn_analyzer/syn_checker.c \$
					parser/ast/ast.c \$
					parser/ast/ast_printer.c \$
					parser/ast/ast_freer.c \$
					parser/ast/ast_node_creator/cmd_node.c \$
					parser/ast/ast_node_creator/operator_node.c \$
					parser/ast/ast_node_creator/subsh_node.c \$
					parser/parser_utils/parser_checker.c \$
					parser/parser_utils/parser_checker2.c \$
					parser/parser_utils/parser.c \$
					error/msg_error.c \$
					exec/exec.c \$
					exec/redirections/heredoc.c \$
					exec/redirections/heredoc_utils.c \$
					exec/redirections/redir.c \$
					exec/redirections/redirection.c \$
					exec/builtins/builtins.c \$
					exec/pipe/error_handling.c \$
					exec/pipe/pipe_handling.c \$
					exec/pipe/process_handling.c \$
					exec/pipe/exec_utils.c \$
					exec/pipe/pipe.c \$
					exec/pipe/pipe_utils.c \$
					exec/builtins/echo.c \$
					exec/builtins/env.c \$
					exec/builtins/pwd.c \$
					utils/lib/lib_checker.c \$
					utils/lib/lib_len.c \$
					utils/lib/lib_memory.c \$
					utils/lib/lib_cmp.c \$
					utils/lib/split.c \$
					utils/free.c \$
					env/env_initializer.c$
$
SRCS        := $(SRCS:%=$(SRC_DIR)/%)$
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)$
$
CC				:= cc$
CFLAGS			:= -Wall -Wextra -Werror$
CPPFLAGS    	:= -I includes$
FSANITIZE_FLAG	:= -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -fstack-protector-strong -fno-optimize-sibling-calls $
$
RM				:= rm -rf$
DIR_DUP     	= mkdir -p $(@D)$
$
# Color$
DEF_COLOR	= \033[0;39m$
RED 		= \033[0;36m$
$
all: $(NAME)$
$
$(NAME): $(OBJS)$
	$(CC) $(OBJS)  -lreadline -o $(NAME)$
$
$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c$
	$(DIR_DUP)$
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<$
$
make run : $(NAME)$
	./minishell$
$
clean:$
	$(RM) $(OBJS)$
	$(RM) $(OBJ_DIR)$
	@echo "$(RED)Minishell objects cleaned!$(DEF_COLOR)"$
$
fclean: clean$
	$(RM) $(NAME)$
	@echo "$(RED)Minishell cleaned!$(DEF_COLOR)"$
$
re:	fclean all$
	@echo "$(RED)Cleaned and rebuilt!$(DEF_COLOR)"$
$
.PHONY: all clean fclean re$
$
# $(FSANITIZE_FLAG)$
