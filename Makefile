NAME = minishell

SRC = SRCS/main.c \
	  SRCS/PARSING/line_to_tkn.c \
	  SRCS/PARSING/pars_func.c \
	  SRCS/PARSING/pars_func2.c \
	  SRCS/PARSING/tkn_to_exe.c \
	  SRCS/PARSING/parser.c \
	  SRCS/PARSING/dblquote_shits.c \
	  SRCS/UTILS/utils1.c \
	  SRCS/UTILS/frag_manager.c \
	  SRCS/UTILS/env_lst.c \
	  SRCS/EXE/exec.c \
	  SRCS/EXE/pipe_loop.c \
	  SRCS/EXE/builtins.c \
	  SRCS/EXE/builtins2.c \


LIBFT = -L./LIBFT -lft

READLINE = -L/usr/local/lib -I/usr/local/include -lreadline

CC = gcc #clang

INC = -I./minishell.h

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

RM = rm -rf

OBJ = $(SRC:.c=.o)
DIROBJ = objs/
DIROBJS = $(addprefix $(DIROBJ), $(OBJ))

all:MLIBFT $(NAME)

MLIBFT:
	@$(MAKE) -C ./LIBFT

$(DIROBJ)%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling: $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(DIROBJS) 
	@echo Creating executable $(NAME)
	@$(CC) $(DIROBJS) $(CFLAGS) -o $(NAME) $(INC) $(LIBFT) $(READLINE)

clean:
	@$(RM) $(DIROBJ)
	@$(MAKE) clean -C ./LIBFT

fclean: clean
	@$(MAKE) fclean -C ./LIBFT
	@$(RM) $(SAVE)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
