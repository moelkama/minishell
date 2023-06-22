/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:36:07 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/15 19:34:50 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>

int	g_status[3];

typedef struct s_command
{
	char	**cmd;
	char	*path;
}			t_command;

typedef struct s_pipe
{
	t_command		*cmd;
	int				in;
	int				out;
	int				here_doc;
	struct s_pipe	*next;
}					t_pipe;

typedef struct s_list
{
	char			*var;
	char			*key;
	int				sort;
	struct s_list	*next;
}			t_list;

int		check_in(char **arr, int i);
char	*returnstr(char *s, int start, int len);
int		ft_isnum(int c);
int		ft_isalpha(int c);
long	ft_atoi(const char *str);
t_pipe	*get_pipes(char *line, char **env);
void	free_pipes(t_pipe **pipes, char **line, char **my_env);
t_pipe	*here_doc(char **arr, char **env);
t_pipe	*newpipe(void);
t_pipe	*lastpipe(t_pipe *pipes);
int		ft_lstsize(t_list *lst);
int		ft_lstsize_pipe(t_pipe *pipe);
int		openfile(char *file, int mode);
t_list	*ft_lstnew(char *key, char *var, int sort);
char	*get_line(char **env);
int		quotes_error(char *line);
int		pipe_error(char **arr);
char	*get_var(char **env, char *var);
void	get_files(t_pipe *pipes, char **arr, char **env, int k);
t_list	*ft_lstlast(t_list *lst);
char	*add_vars(char *line, char **env, int d, int s);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*get_var(char **env, char *var);
char	*findpath(char *envpath, char *cmd);
char	*findpath(char *envpath, char *cmd);
void	get_commands(t_pipe *pipes, char **env, char **arr);
int		check_qutes(char *limit);
int		ft_cat(char *line, char *new, char *sp, int i);
void	check_herdoc(char **arr);
char	*remove_quotes(char *line);
int		manage_quotes(char *line, int i, int *d, int *s);
char	*manage_symbol(char *line);
char	*manage_pipe(char *line);
int		symbol_error(char **arr);
int		ft_count_strs(char *str, char *c);
char	**ft_split(char *str, char *c);
char	**ft_free(char **strs);
char	*ft_link(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
int		is_exist(char *str, char c);
void	ft_strncopy(char *dest, char *src, int n);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *str, int fd, int endl);
int		is_valid(int c);
int		ft_nbrlen(int n);
char	*ft_itoa(int n);
void	rl_replace_line(const char *text, int clear_undo);
int		ft_strcmp(char *str1, char *str2);
void	ft_sortlist(t_list *ptr);
void	ft_echo(char **str, char *option);
void	ft_get_env(char **env, t_list **ptr, int show);
void	ft_export(char **export, t_list **ptr, int show);
void	get_var_key(char *env, t_list **ptr, int show);
int		ft_check_export(char *str);
void	ft_cd(char *path, t_list **ptr, int sort);
char	*ft_delete_dirname(char *str);
void	ft_unset(char **unset, t_list **ptr, int show);
int		ft_check_echo(char *option);
void	get_pwd(void);
void	ft_printf(char *str, char *s);
char	**ft_change_type(t_list *ptr);
void	ft_exit(char **ext, int show);
char	*to_lowor(char *s1);
char	*ft_alloc(char *str);
void	ft_multiple_cmd(t_pipe *ptr, char **env, t_list **linked_env);
void	ft_free_env(char **ptr);
void	handel_ctrlc(int sig);
void	ft_echo(char **str, char *option);
int		check_if_exit(t_list *ptr, char *str);
int		ft_check_unset(char *unset);
char	*ft_find_var(t_list	*ptr, char *path);
int		ft_check_export(char *str);
char	*ft_strcat(char *s1, char *s2);
char	*ft_return_str(char	*str);
void	ft_signals(int h);
void	ft_puterror(char *cmd, char *cmd1);
int		ft_check_builtin(char *cmd, char *cmd1);
char	*ft_alloction(char *s1, char *s2);
int		ft_check_pwd(char *pwd, t_list *ptr);
void	printerr(int show, char *path);
void	ft_remove2(t_list **ptr, char *unset);
void	ft_remove(t_list **ptr);
void	add_or_create2(t_list *head, char *var, t_list **ptr, char *export);
int		ft_check_ifadd(t_list **ptr, char *str);
char	*ft_give_key(char *str);
void	wait_checksignal(int *std);
int		ft_check(char *str);
int		if_exist(char *str, char c);
void	ft_cmd_error(t_list *linked_env, t_pipe *ptr);

#endif
