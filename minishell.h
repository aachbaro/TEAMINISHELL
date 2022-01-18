/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:39:23 by aachbaro          #+#    #+#             */
/*   Updated: 2022/01/14 18:18:14 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

# define TYPE_NAME 0
# define TYPE_QUOTE 1
# define TYPE_DBLQUOTE 2
# define TYPE_VAR 3
# define TYPE_REDIN 4
# define TYPE_REDOUT 5
# define TYPE_HRDOC 6
# define TYPE_APPEND 7

typedef struct s_dblquote_parser
{
	int	i;
	int	j;
	char	*str;
	char	*tmp;
	char	*tmp2;
}		t_dblquote_parser;

typedef struct s_tkn
{
	char			*content;
	int				type;
	struct s_tkn	*prev;
	struct s_tkn	*next;
}					t_tkn;

typedef struct s_cmd
{
	char	*line;
	char	*path;
	char	**args;
	t_tkn	*tkn;
}			t_cmd;

typedef struct s_envar
{
	char			*str;
	struct s_envar	*next;
}					t_envar;

typedef struct s_data
{
	char	*line;
	char	*old_line;
	t_cmd	*cmds;
	int		over;
	t_envar	*env;
	char	**in_env;
}			t_data;

// PARSER DE COMMANDE
int 	check_quote(char *str);
int		split_cmds(t_data *data, char *str);
int		line_to_tokens(t_data *data);
int		pars_alnum(t_data *data, int start, int cmd);
int		pars_quote(t_data *data, int start, int cmd);
int		get_dblquote_size(t_data *data, int start, int cmd);
char		*recup_var(t_data *data, int start, int cmd);
char		*find_var(char *var, t_envar *env);
void		fill_dblquote(t_data *data, int start, int cmd);
int		pars_dblquote(t_data *data, int start, int cmd);
int		pars_lessthan(t_data *data, int start, int cmd);
int		pars_morethan(t_data *data, int start, int cmd);
int		pars_var(t_data *data, int start, int cmd);
int		tkn_to_exe(t_data *data, int cmd);
int		line_to_exe(t_data *data);
int		inputing(t_data *data);

// ELSE
int	prompt(t_data *data);

// EXECUTION
void	exe_path(t_data *data, int cmd);
int	exe_builtin(t_data *data, int cmd);
void	exe_cmds(t_data *data);
int	is_builtin(t_cmd cmd);
void	pipe_loop(t_data *data);
int	built_pwd(t_cmd cmd);
void	built_echo(t_cmd cmd);
void	built_env(t_envar *env);
void	built_cd(t_cmd cmd);

// UTILS INUTILS
void	aff_lst(t_list *lst);
void	delst(void	*content);
void	del_tab(char **tab);
void	del_cmd(t_data *data);
char	*ft_strndup(const char *s, int n);
void	free_all(t_data *data);

//INIT
void	shell_start(t_data *data, char **env);

// FRAG UTILS
t_tkn	*tkn_new(char *content, int type);
t_tkn	*tkn_last(t_tkn *cmd);
void	tkn_addback(t_tkn **cmd, t_tkn *new);
void	tkn_clear(t_tkn **cmd);

//env
t_envar	*init_env(char **env);
t_envar	*add_env(t_envar **lst, char *str);

//signals
void	sig_config(void);

#endif
