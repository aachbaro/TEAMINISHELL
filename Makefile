NAME = minishell

SRC = srcs/main.c \
	  srcs/wait_input.c \
	  srcs/parsing/parser.c \
	  srcs/parsing/parser_utils.c \
	  srcs/parsing/parser_utils2.c \
	  srcs/parsing/tokenisation.c \
	  srcs/parsing/tokenisation2.c \
	  srcs/parsing/set_redirections.c \
	  srcs/parsing/search_executable.c \
	  srcs/parsing/pars_error.c \
	  srcs/exe/exec_builtins.c \
	  srcs/exe/exec_pipe.c \
	  srcs/exe/builtins/built_cd.c \
	  srcs/exe/builtins/built_echo.c \
	  srcs/exe/builtins/built_env.c \
	  srcs/exe/builtins/built_pwd.c \
	  srcs/exe/builtins/built_unset.c \
	  srcs/exe/builtins/built_export.c \
	  srcs/exe/redirections/heredoc.c \
	  srcs/exe/redirections/redirection_handler.c \
	  srcs/init/shell_start.c \
	  srcs/utils/delete_cmd.c \
	  srcs/utils/delete_tab.c \
	  srcs/utils/free_all.c \
	  srcs/utils/tkn_lst.c \
	  srcs/env_utils/env_lst.c \
	  srcs/env_utils/display_env.c \
	  srcs/env_utils/free_envar.c \
	  srcs/env_utils/find_envar.c \
	  srcs/env_utils/lst_to_tab.c \
	  srcs/env_utils/change_env.c \
	  srcs/env_utils/env_size.c \
	  srcs/signals/sig_config.c \
	  srcs/debug/utils1.c \
	  srcs/debug/debug.c \
	  srcs/utils/exit.c

libft = -Llibft/ -lft

READLINE = -L/usr/local/lib -I/usr/local/include -lreadline

CC = gcc #clang

INC = -Iminishell.h

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

RM = rm -rf

OBJ = $(SRC:.c=.o)
DIROBJ = objs/
DIROBJS = $(addprefix $(DIROBJ), $(OBJ))

all:LIBFT $(NAME)

LIBFT:
	@$(MAKE) -C libft/

$(DIROBJ)%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling: $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(DIROBJS) 
	@echo Creating executable $(NAME)
	@$(CC) $(DIROBJS) $(CFLAGS) -o $(NAME) $(INC) $(libft) $(READLINE)

clean:
	@$(RM) $(DIROBJ)
	@$(MAKE) clean -C libft/

fclean: clean
	@$(MAKE) fclean -C libft/
	@$(RM) $(SAVE)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
