/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:39:23 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/09 20:02:50 by aachbaro         ###   ########.fr       */
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
	int		i;
	int		j;
	char	*str;
	char	*tmp;
	char	*tmp2;
	int		smpl;
	int		dbl;
	int		k;
}		t_dblquote_parser;

typedef struct s_tkn
{
	struct s_tkn	*next;
	struct s_tkn	*prev;
	char			*content;
	int				type;
	int				space;
	int				quotes;
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
	t_redirtools	redir;
	int				fds[2];
	int				old_fds[2];
	int				pid;
	int				status;
	int				save_stdin;
	int				save_stdout;
}			t_pipetools;

typedef struct s_data
{
	char		*usr_input;
	char		*prev_input;
	t_cmd		*cmds;
	int			heredoc_id;
	int			over;
	t_envar		*env;
	char		**in_env;
	int			exit_status;
}			t_data;

typedef struct s_glob
{
	int	exit;
	int	status;
	t_data	*data;
}	t_glob;

extern t_glob	g_g;

// PARSER DE COMMANDE
int		check_quote(char *str);
int		split_cmds(t_data *data, char *str);
int		line_to_tokens(t_data *data);
int		tkn_alnum(t_data *data, int start, int cmd);
int		tkn_quote(t_data *data, int start, int cmd);
int		get_dblquote_size(t_data *data, int start, int cmd);
char	*recup_var(t_data *data, int start, int cmd);
char	*find_var(char *var, t_envar *env, int exit_status);
void	fill_dblquote(t_data *data, int start, int cmd);
int		tkn_dblquote(t_data *data, int start, int cmd);
int		tkn_lessthan(t_data *data, int start, int cmd);
int		tkn_morethan(t_data *data, int start, int cmd);
int		tkn_var(t_data *data, int start, int cmd);
int		tkn_to_exe(t_data *data, int cmd);
int		input_to_exe(t_data *data);
int		input_to_tokens(t_data *data);
int		redir_in_tkns(t_data *data);
int		set_redir(t_cmd *cmd);
void	init_redirtool(t_redirtools *redir);
int		chckinfsup(t_data *data);
int		chckcmdinfsup(t_cmd *cmd);
int		spaces_between_tkns(t_data *data);
int		merge_tokens(t_cmd *cmd);
int		inputing(t_data *data);
int		cmd_to_tokens(char *str, t_data *data, int cmd);
int		set_heredoc(t_cmd *cmd, int *heredoc_id, t_data *data);
int		init_heredoc(t_tkn *tkn, int heredoc_id, t_data *data);
int		init_heredoc2(char **heredoc_name, t_pipetools *fork);
char	*filename_generator(int heredoc_id);
void	heredoc_loop(int fd, char *delim, t_data *data, int quotes);
void	heredoc_loop2(int fd, char *input, int quotes, t_data *data);
char	*treat_heredoc_input(char *input, t_data *data);
int		treat_hdinput2(char *input, t_data *data, t_dblquote_parser *pars);
char	*var_name(char *str);
char	**get_args(t_cmd cmd);
char	*get_path(char *cmd, t_envar *env);
char	*get_possible_path(char *cmd, char *str);
int		in_loop(t_data *data, int cmd, t_dblquote_parser *pars);
int		merge_tokens2(t_tkn *cpy);
int		check_empty_pipe(t_data *data);
char	**split_pipe(char *str);

// ELSE
int		prompt(t_data *data);

// EXECUTION
void	exe_path(t_data *data, int cmd);
int		exe_builtin(t_data *data, int cmd);
void	exe_cmds(t_data *data);
int		is_builtin(t_cmd cmd);
int		pipe_loop(t_data *data);
int		exe_simple_cmd(t_data *data);
int		built_pwd(t_cmd cmd);
int		built_echo(t_cmd cmd);
int		built_env(t_envar *env);
int		built_cd(t_cmd cmd, t_data *data);
int		built_unset(t_cmd cmd, t_data *data);
int		built_exit(t_cmd cmd, t_data *data);
int		is_builtin(t_cmd cmd);
int		exec_pipe(t_data *data);
void	exec_pipe2(t_pipetools *pipes, t_data *data, int i);
void	save_initial_fds(t_pipetools *pipes);
void	child_process(t_pipetools *pipes, t_data *data, int i);
void	child_process_init(t_pipetools *pipes, t_data *data, int i);
void	parent_process(t_pipetools *pipes, t_data *data, int i);
void	restaure_initial_fds(t_pipetools *pipes, int i);
int		init_fds_redir(t_cmd cmd, t_redirtools *redir);
void	restaure_fds_redir(t_redirtools *redir);
int		get_fds_redir(t_cmd, t_redirtools *redir);
int		init_redin(t_tkn tkn);
int		init_redout(t_tkn tkn);
int		built_export(t_cmd cmd, t_data *data);
void	empty_input(t_data *data);
char	*get_cmd_name(t_cmd cmd);

// UTILS INUTILS
void	aff_lst(t_list *lst);
void	delst(void	*content);
void	del_tab(char **tab);
void	del_cmd(t_data *data);
void	free_all(t_data *data);
int		ft_error(char *msg, int exit_num);
int		expand_exit(int exit, int ret);
void	exit_child(t_data *data, t_pipetools *pipes);

//INIT
int		shell_start(t_data *data, char **env);

// TKN UTILS
t_tkn	*tkn_new(char *content, int type);
t_tkn	*tkn_last(t_tkn *cmd);
void	tkn_addback(t_tkn **cmd, t_tkn *new);
void	tkn_clear(t_tkn **cmd);

//env
t_envar	*init_env(char **env);
t_envar	*add_env(t_envar **lst, char *str);
//int	delete_env(t_envar **lst, char *name);
int		remove_var(t_envar **env, char *key);
t_envar	*find_envar(t_envar *lst, char *name);
void	free_envar(t_envar *var);
int		ft_isexported(t_envar *lst, char *name);
void	display_env(t_envar *env, int flag);
t_envar	*change_env(t_envar **envar, char *to);
char	**lst_to_tab(t_envar *env);
int		env_size(t_envar *env);

//signals
void	sig_config(void);
void	signal_handler(int sig);

#endif
