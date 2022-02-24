/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:39:23 by aachbaro          #+#    #+#             */
/*   Updated: 2022/02/24 16:57:18 by aachbaro         ###   ########.fr       */
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
	char		*content;
	int		type;
	int		space;
	int		quotes;
	struct s_tkn	*prev;
	struct s_tkn	*next;
}			t_tkn;

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
	char			*key;
	char			*value;
	struct s_envar	*next;
}					t_envar;

typedef struct s_redirtools
{
	int	save_stdin;
	int	save_stdout;
	int	fd_in;
	int	fd_out;
}		t_redirtools;

typedef struct s_pipetools
{
	int		fds[2];
	int		old_fds[2];
	int		pid;
	int		status;
	int		save_stdin;
	int		save_stdout;
	t_redirtools	redir;
}			t_pipetools;

typedef struct s_data
{
	char		*usr_input;
	char		*prev_input;
	t_cmd		*cmds;
	int		heredoc_id;
	int		over;
	t_envar		*env;
	char		**in_env;
}			t_data;

// PARSER DE COMMANDE
int 	check_quote(char *str);
int		split_cmds(t_data *data, char *str);
int		line_to_tokens(t_data *data);
int		tkn_alnum(t_data *data, int start, int cmd);
int		tkn_quote(t_data *data, int start, int cmd);
int		get_dblquote_size(t_data *data, int start, int cmd);
char		*recup_var(t_data *data, int start, int cmd);
char		*find_var(char *var, t_envar *env);
void		fill_dblquote(t_data *data, int start, int cmd);
int		tkn_dblquote(t_data *data, int start, int cmd);
int		tkn_lessthan(t_data *data, int start, int cmd);
int		tkn_morethan(t_data *data, int start, int cmd);
int		tkn_var(t_data *data, int start, int cmd);
int		tkn_to_exe(t_data *data, int cmd);
int		input_to_exe(t_data *data);
int		input_to_tokens(t_data *data);
int		redir_in_tkns(t_data *data);
int		set_redir(t_cmd *cmd);
int		spaces_between_tkns(t_data *data);
int		merge_tokens(t_cmd *cmd);
int		inputing(t_data *data);
int		cmd_to_tokens(char *str, t_data *data, int cmd);
int		set_heredoc(t_cmd *cmd, int *heredoc_id, t_data *data);
int		init_heredoc(t_tkn *tkn, int heredoc_id, t_envar *envar);
char		*filename_generator(int heredoc_id);
int		heredoc_loop(int fd, char *delim, t_envar *env, int quotes);
char		*treat_heredoc_input(char *input, t_envar *env);
char		*var_name(char *str);
char		**get_args(t_cmd cmd);
char		*get_path(char *cmd);
char 		*get_possible_path(char *cmd, char *str);
int		in_loop(t_data *data, int cmd, t_dblquote_parser *pars);
int		merge_tokens2(t_tkn *cpy);

// ELSE
int	prompt(t_data *data);

// EXECUTION
void	exe_path(t_data *data, int cmd);
int		exe_builtin(t_data *data, int cmd);
void	exe_cmds(t_data *data);
int		is_builtin(t_cmd cmd);
int	pipe_loop(t_data *data);
int	exe_simple_cmd(t_data *data);
int		built_pwd(t_cmd cmd);
void	built_echo(t_cmd cmd);
void	built_env(t_envar *env);
void	built_cd(t_cmd cmd);
int	built_unset(t_cmd cmd, t_envar **env);
int	is_builtin(t_cmd cmd);
int	exec_pipe(t_data *data);
void    save_initial_fds(t_pipetools *pipes);
void    child_process(t_pipetools *pipes, t_data *data, int i);
void    parent_process(t_pipetools *pipes, t_data *data, int i);
void    restaure_initial_fds(t_pipetools *pipes , int i);
int	init_fds_redir(t_cmd cmd, t_redirtools *redir);
void	restaure_fds_redir(t_redirtools *redir);
int	get_fds_redir(t_cmd, t_redirtools *redir);
int	init_redin(t_tkn tkn);
int	init_redout(t_tkn tkn);
void	built_export(t_cmd cmd, t_data *data);
void	empty_input(t_data *data);
char	*get_cmd_name(t_cmd cmd);

// UTILS INUTILS
void	aff_lst(t_list *lst);
void	delst(void	*content);
void	del_tab(char **tab);
void	del_cmd(t_data *data);
void	free_all(t_data *data);

//INIT
void	shell_start(t_data *data, char **env);

// TKN UTILS
t_tkn	*tkn_new(char *content, int type);
t_tkn	*tkn_last(t_tkn *cmd);
void	tkn_addback(t_tkn **cmd, t_tkn *new);
void	tkn_clear(t_tkn **cmd);

//env
t_envar	*init_env(char **env);
t_envar	*add_env(t_envar **lst, char *str);
void	delete_env(t_envar **lst, char *name);
t_envar	*find_envar(t_envar **lst, char *name);
void	free_envar(t_envar *var);
int	ft_isexported(t_envar *lst, char *name);

//signals
void	sig_config(void);

#endif
