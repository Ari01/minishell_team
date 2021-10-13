/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:44 by dchheang          #+#    #+#             */
/*   Updated: 2021/10/13 11:25:24 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include <assert.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include "libft/libft.h"

/*
 **	ERRORS
 */
# define SYNTAX_ERR		1
# define PIPE_ERR		2
# define FILE_ERR		3
# define READ_WRITE_ERR 4
# define EXEC_ERR		5

/*
 **	READ WRITE
 */
# define BUFFER_SIZE 100000

/*
 **	PIPE AND REDIRECTION
 */
# define PIPE '|'
# define SLR '<'
# define DLR 1
# define SRR '>'
# define DRR 2
# define ERROR 1
# define SUCCESS 0

# define TO_MERGE 1
# define NO_TOUCH 2
# define STATUS_OPEN 1
# define STATUS_CLOSE 0
# define IS_SQ 1
# define IS_DQ 2
# define NO_Q 0
# define IS_DOLLAR 1

typedef struct s_quot
{
	int	quot;
	int	quot_status;
}		t_quot;

/*
 **	TOKENS
 */
# define CMD_TOK 0
# define PIPE_TOK 1
# define REDIR_TOK 2

/*
 **	COMMANDS
 */
# define BUILTINS "cd echo env exit export pwd unset"

/*
 ** STRUCT
 */
typedef struct s_token
{
	char	*value;
	int		id;
}		t_token;

typedef struct s_history
{
	int		fd;
	char	*path;
}		t_history;

typedef struct s_ms
{
	char		*rdl;
	char		**envp;
	int			fd_in;
	int			fd_out;
	t_list		*cmd_list_head;
	t_list		*cmd_list_ite;
	t_list		*env_list;
	t_history	history;
	int			cmd_ret;
}		t_ms;

/*
 **	PARSING
 */
typedef struct s_io
{
	int		flag;
	char	*file;
}		t_io;

typedef struct s_cmd
{
	char	**cmd;
	t_list	*in_streams;
	t_list	*in_stream_head;
	t_list	*out_streams;
	t_list	*out_streams_head;
	int		flag;
}		t_cmd;

typedef struct s_cmdinfo
{
	char	*cmd;
	int		status;
}		t_cmdinfo;

typedef struct s_dollar
{
	int		i;
	int		start;
	int		len;
	char	*dollar;
	char	*new_cmd;
	char	*c;
}		t_dollar;

typedef struct s_quotinfo
{
	int			i;
	int			len;
	char		*new_cmd;
	t_list		*list1;
	t_cmdinfo	*cmdinfo;
}		t_quotinfo;

/*
 ** HISTORY
*/
t_history	init_history(t_history history);
void		ft_add_history(char *cmd, t_history history);
void		ft_interrupt(int signe);
/*
 **	ERRORS
 */
void		free_cmd(void *content);
void		free_memory(t_ms *ms);
void		print_error_msg(char *s, int error_id, t_ms *ms);
/*
 **	LEXER
 */
void		free_token(void *content);
t_list		*get_tokens(char *s);
/*
 **	GRAMMAR
 */
char		*check_grammar(t_list *token_list);
/*
 **	PARSER
 */
int			check_rdl(t_ms *ms);
t_list		*get_cmds(char *s, t_list *env_list, t_ms *ms);
t_list		*get_stream(t_list *cmd_list);

/*
 **	PARSER_UTILS
 */
int			is_redir(int flag);
t_list		*remove_current_ite(t_list **cmd_list, t_list *ite);
void		reset_array(char **array);
t_cmd		new_io_cmd(void);
t_list		*ft_trim(t_list *cmd_list);
/*
 **  BUILTINS
 */
int			is_builtin(char *s);
int			ft_echo(t_cmd *cmd);
int			ft_cd(t_cmd *cmd);
int			ft_pwd(void);
int			ft_exit(t_cmd *cmd);
int			ft_env(t_list *env_list, t_cmd *cmd);
int			ft_export(t_cmd *cmd, t_list *env_list);
int			check_is_name(char *s);
int			check_change(char *s);
int			ft_unset(t_cmd *cmd, t_list **env_list);
void		ft_list_sort(t_list **begin_list, int (*ft_strcmp)());
void		print_msg(char *msg1, char *msg2, char *msg3, int fd);
t_list		*check_name_exist(char *cmd, t_list *env_list);
t_list		*get_env(char **env, t_list *env_list);
/*
 **	PIPE
 */
int			run_pipe(t_ms *ms);
/*
 **	REDIRECTION
 */
void		reset_fdin_fdout(t_ms *ms);
void		redirect(t_ms *ms, t_cmd *current_cmd);
/*
 **	COMMANDS
 */
int			run_cmd(t_ms *ms, t_cmd *cmd);
/*
 **	EXEC
 */
int			run_exec(t_ms *ms, t_cmd *cmd);
void		run_shell(char **env);
/*
 **	UTILS
 */
void		print_cmds(t_list *cmd_list);
void		free_array(char **array);
void		remove_elem_from_array(char **array);
void		remove_from_list(t_list **head, t_list *elem);
char		**array_join(char **a1, char **a2);

/*
 **	VARS
 */
void		print_var_list(t_list *env_list);
char		*get_var(t_list *env_list, char *name);

/*
 **	SIGNAL
 */
void		catch_sig(int signum);

/*
 **	PARSING
 */
size_t		ft_len(const char *s);
char		*ft_join(char const *s1, char const *s2);
int			check_flag(char *cmd, int i);
char		**lst_to_tab(char *cmd, t_list *env_list, t_ms *ms);
int			is_flag(char c);
char		*hanlding_dollar(char *cmd, t_list *env_list, t_ms *ms);
int			check_env_len(char *env);
int			check_env_start(char *env);
int			check_dollar(char *cmd);
void		check_status(char c, t_quotinfo *quotinfo);
void		parser_dollar(t_quotinfo *quotinfo, t_list *env_list, t_ms *ms);
t_list		*part_nq(char *cmd, t_list *env_list,
				t_ms *ms, t_quotinfo *quotinfo);
t_list		*part_sq(char *cmd, t_quotinfo *quotinfo);

t_list		*part_dq(char *cmd, t_list *env_list,
				t_ms *ms, t_quotinfo *quotinfo);
t_cmdinfo	*creat_cmdinfo(void);
t_quot		quote_init(void);
t_quotinfo	quotinfo_init(void);
t_list		*sepa_cmd(char *cmd, t_list *env_list, t_ms *ms);
t_cmd		*init_cmd(void);
t_list		*check_env_exit(char *dollar, t_list *env_list);
t_dollar	init_dollar(void);
char		*ft_strlowcase(char *str);
int			_wstatus(int status);
int			_wifexited(int status);
int			_wexitstatus(int status);
int			_wifsignaled(int status);
int			_wtermsig(int status);

#endif