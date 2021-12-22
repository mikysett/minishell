MAKEFLAGS	+=	--quiet

WHT	= \033[0;37m
BLK	= \033[0;30m
RED	= \033[0;31m
YEL	= \033[0;33m
BLU	= \033[0;34m
GRN	= \033[0;32m

NAME	=	minishell

LIBFT	=	libft/libft

HEADERS	=	headers

DIR_S	=	srcs

DIR_O	=	obj

# Using wildcards: $(shell find $(DIR_S) -name *.c)
BASIC_SRCS	:=	srcs/cmd_builtin/cd_builtin.c \
				srcs/cmd_builtin/cmd_builtin_util.c \
				srcs/cmd_builtin/echo_builtin.c \
				srcs/cmd_builtin/env_builtin.c \
				srcs/cmd_builtin/exit_builtin.c \
				srcs/cmd_builtin/export_builtin.c \
				srcs/cmd_builtin/pwd_builtin.c \
				srcs/cmd_builtin/unset_builtin.c \
				srcs/core/core_util.c \
				srcs/core/free_mem.c \
				srcs/core/free_mem_util.c \
				srcs/core/memory_util.c \
				srcs/core/redir_util.c \
				srcs/environment/env_accessors.c \
				srcs/environment/env_print.c \
				srcs/environment/env_vars.c \
				srcs/environment/envp.c \
				srcs/executor/exec_std_cmd.c \
				srcs/executor/executor.c \
				srcs/executor/make_redir.c \
				srcs/executor/set_cmd_path.c \
				srcs/executor/setup_redirect.c \
				srcs/executor/std_io_streams.c \
				srcs/executor/std_io_streams_util.c \
				srcs/get_next_line/get_next_line.c \
				srcs/get_next_line/get_next_line_utils.c \
				srcs/interactive_mode.c \
				srcs/main.c \
				srcs/non_interactive_mode.c \
				srcs/parser/filename_expansion.c \
				srcs/parser/filename_expansion_util.c \
				srcs/parser/lexer.c \
				srcs/parser/lexer_util.c \
				srcs/parser/parameter_expansion.c \
				srcs/parser/parameter_expansion_util.c \
				srcs/parser/parser.c \
				srcs/parser/parser_creators.c \
				srcs/parser/parser_tasks.c \
				srcs/parser/parser_util_getters.c \
				srcs/parser/perform_expansions.c \
				srcs/parser/quote_removal.c \
				srcs/parser/quote_util.c \
				srcs/parser/tokens.c \
				srcs/parser/validate_grammar.c \
				srcs/debug.c

SRCS		:= $(BASIC_SRCS)


BONUS_SRCS	:= $(BASIC_SRCS)

OBJS		:= $(SRCS:%.c=$(DIR_O)/%.o)

BONUS_OBJS	:= $(BONUS_SRCS:%.c=$(DIR_O)/%.o)

SUB_DIR_O := $(shell find $(DIR_S) -type d)
SUB_DIR_O := $(SUB_DIR_O:%=$(DIR_O)/%)

# Using wildcards: $(shell find $(HEADERS) -name *.h)
DEPS	=	$(shell find $(HEADERS) -name *.h)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror
INCLUDES	= -I $(HEADERS) -I $(LIBFT)

LIBS	=	-L./$(LIBFT) -lft -lreadline

RM		=	rm -f

$(DIR_O)/%.o: %.c
			@mkdir -p $(DIR_O)
			@mkdir -p $(SUB_DIR_O)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME):	$(DEPS) $(OBJS)
			@make $(FAST)bonus -C $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)
			printf "$(WHT)[$(GRN)$(NAME) COMPILED$(WHT)]\n"

all:		$(NAME)

bonus:		$(DEPS) $(BONUS_OBJS)
			@make $(FAST)bonus -C $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(BONUS_OBJS) $(LIBS)
			printf "$(WHT)[$(GRN)$(NAME) BONUS COMPILED$(WHT)]\n"

miniclean:
			$(RM) $(OBJS)
			$(RM) $(BONUS_OBJS)
			printf "$(WHT)[$(YEL)$(NAME) OBJS REMOVED$(WHT)]\n"

clean:		miniclean
			@make clean -C $(LIBFT)

fclean:		miniclean
			$(RM) $(NAME)
			@make fclean -C $(LIBFT)
			printf "$(WHT)[$(YEL)$(NAME) BINARIES REMOVED$(WHT)]\n"

re:			fclean all

debug:		INCLUDES += -DDEBUG_MODE
debug:		CFLAGS = -Wall -Wextra -g -fsanitize=address
debug:		miniclean
debug:		all

.PHONY:		all bonus miniclean clean fclean re debug