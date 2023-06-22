/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:40:40 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/15 19:37:39 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_in(char **arr, int i)
{
	while (arr[i])
	{
		if (!ft_strcmp(arr[i], "<") || !ft_strcmp(arr[i], "<<"))
			return (0);
		else if (!ft_strcmp(arr[i + 1], "|"))
			return (1);
		i++;
	}
	return (1);
}

void	ft_read(char *limit, char **env, int fd, int k)
{
	char	*line;
	char	*new;
	char	*ex_it;
	int		vars;

	vars = 1;
	if (check_qutes(limit))
		vars = 0;
	line = readline("> ");
	ex_it = remove_quotes(limit);
	while (line && ft_strcmp(line, ex_it))
	{
		if (vars == 1)
			new = add_vars(line, env, 0, 0);
		else
			new = line;
		if (k == 1)
			ft_putstr_fd(new, fd, 1);
		free(line);
		if (vars == 1)
			free(new);
		line = readline("> ");
	}
	exit(0);
	free(ex_it);
}

void	handel_heredoc(int sig)
{
	(void)sig;
	exit(1);
}

int	read_doc(char **arr, char **env, int i)
{
	int		fd[2];
	int		k;

	k = 0;
	if (check_in(arr, i) && pipe(fd) != -1)
		k = 1;
	g_status[1] = 3;
	if (g_status[2] == 0 && fork() == 0)
	{
		signal(SIGINT, handel_heredoc);
		signal(SIGQUIT, SIG_IGN);
		if (arr[i][0] == '"' || arr[i][0] == '\'')
			ft_read(arr[i], env, fd[1], k);
		else
			ft_read(arr[i], env, fd[1], k);
		exit (0);
	}
	wait(g_status);
	if (*g_status)
		g_status[2] = 1;
	close(fd[1]);
	if (k == 0)
		return (-1);
	return (fd[0]);
}

t_pipe	*here_doc(char **arr, char **env)
{
	t_pipe	*pipe;
	t_pipe	*ptr;
	int		i;

	i = 0;
	check_herdoc(arr);
	pipe = newpipe();
	while (arr[i])
	{
		ptr = lastpipe(pipe);
		if (!ft_strcmp(arr[i], "<<"))
		{
			ptr->in = read_doc(arr, env, i + 1);
			if (ptr->in > 0)
				ptr->here_doc = 1;
		}
		else if (!ft_strcmp(arr[i], "|"))
			ptr->next = newpipe();
		i++;
	}
	return (pipe);
}
