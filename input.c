/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:50:06 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/15 19:43:51 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*newpipe(void)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->in = -1;
	pipe->out = -1;
	pipe->here_doc = 0;
	pipe->cmd = NULL;
	pipe->next = NULL;
	return (pipe);
}

int	openfile(char *file, int mode)
{
	DIR	*dir;
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	dir = opendir(file);
	if (fd == -1 || (dir && mode != 0))
		ft_putstr_fd(file, 2, 0);
	if (!access(file, F_OK) || dir || mode != 0)
	{
		if (mode != 0 && dir)
			return (ft_putstr_fd(" : Is a directory", 2, 1), fd);
		if (mode == 0 && access(file, R_OK))
			return (ft_putstr_fd(" : Permission denied", 2, 1), -2);
		if (mode != 0 && access(file, W_OK))
			return (ft_putstr_fd(" : Permission denied", 2, 1), -2);
	}
	else
		return (ft_putstr_fd(" : No such file or directory", 2, 1), -2);
	return (fd);
}

int	check_valid(t_pipe *ptr, char **arr, char **env, int i)
{
	char	*with_var;

	with_var = add_vars(arr[i + 1], env, 0, 0);
	if (!with_var[0] && ptr->in != -2 && ptr->out != -2)
	{
		if (!ft_strcmp(arr[i], ">") || !ft_strcmp(arr[i], ">>"))
		{
			ft_putstr_fd(arr[i + 1], 2, 0);
			ft_putstr_fd(" : ambiguous redirect", 2, 1);
			ptr->out = -2;
			free(with_var);
			return (1);
		}
		else if (!ft_strcmp(arr[i], "<"))
		{
			ft_putstr_fd(arr[i + 1], 2, 0);
			ft_putstr_fd(" : ambiguous redirect", 2, 1);
			ptr->in = -2;
			free(with_var);
			return (1);
		}
	}
	free(with_var);
	return (0);
}

void	get_fd(t_pipe *pipes, char **arr, int i, char *file)
{
	int	fd;

	if (!ft_strcmp(arr[i], "<") && pipes->in != -2 && pipes->out != -2)
	{
		fd = openfile(file, 0);
		if (pipes->here_doc == 0)
			pipes->in = fd;
	}
	else if (!ft_strcmp(arr[i], ">") && pipes->in != -2 && pipes->out != -2)
		pipes->out = openfile(file, 1);
	else if (!ft_strcmp(arr[i], ">>") && pipes->in != -2 && pipes->out != -2)
		pipes->out = openfile(file, 2);
}

void	get_files(t_pipe *pipes, char **arr, char **env, int i)
{
	char	*file;
	char	*with_var;

	while (arr[++i])
	{
		if (check_valid(pipes, arr, env, i))
		{
			i++;
			continue ;
		}
		with_var = add_vars(arr[i + 1], env, 0, 0);
		file = remove_quotes(with_var);
		get_fd(pipes, arr, i, file);
		if (!ft_strcmp(arr[i], "|"))
			pipes = pipes->next;
		free(with_var);
		free(file);
	}
}
