NAME = minishell

SRC = srcs/main.c \
	  srcs/parsing/input_to_tkn.c \
	  srcs/parsing/pars_func.c \
	  srcs/parsing/tkn_to_exe.c \
	  srcs/parsing/parser.c \
	  srcs/parsing/wait_input.c \
	  srcs/parsing/pars_func_dblquote.c \
	  srcs/parsing/redir_in_tkns.c \
	  srcs/parsing/handle_spaces.c \
	  srcs/debug/utils1.c \
	  srcs/utils/tkn_lst.c \
	  srcs/debug/debug.c \
	  srcs/utils/delete_cmd.c \
	  srcs/utils/delete_tab.c \
	  srcs/utils/free_all.c \
	  srcs/env_utils/env_lst.c \
	  srcs/env_utils/free_envar.c \
	  srcs/env_utils/ft_isexported.c \
	  srcs/exe/exec.c \
	  srcs/exe/pipe_loop.c \
	  srcs/exe/redirection_handler.c \
	  srcs/signals/sig_config.c \
	  srcs/builtins/built_cd.c \
	  srcs/builtins/built_echo.c \
	  srcs/builtins/built_env.c \
	  srcs/builtins/built_pwd.c \
	  srcs/builtins/built_unset.c \
	  srcs/builtins/built_export.c \
	  srcs/init/shell_start.c

libft = -Llibft/ -lft

READLINE = -L/usr/local/lib -I/usr/local/include -lreadline

CC = gcc #clang

INC = -Iminishell.h

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

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
