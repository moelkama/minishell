/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:15:30 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/15 12:14:39 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_link(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len * sizeof(char ) + sizeof(char ));
	if (str)
	{
		i = 0;
		j = 0;
		while (s1 && s1[j])
			str[i++] = s1[j++];
		j = 0;
		while (s2 && i < len)
			str[i++] = s2[j++];
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

t_command	*new_command(char **cmds, char **env)
{
	t_command	*command;
	char		*path;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	path = get_var(env, "PATH");
	command->cmd = cmds;
	command->path = findpath(path, cmds[0]);
	return (command);
}

char	*findpath(char *envpath, char *cmd)
{
	char	**paths;
	char	*path;
	char	*cmd_path;
	int		i;

	if (access(cmd, X_OK) == 0 && (if_exist(cmd, '/')
			|| envpath[ft_strlen(envpath) - 1] == ':'))
		return (ft_link(cmd, NULL));
	if (is_exist(cmd, '/') != -1)
		return (NULL);
	paths = ft_split(envpath, ":");
	i = 0;
	while (paths && paths[i])
	{
		path = ft_link(paths[i], "/");
		cmd_path = ft_link(path, cmd);
		if (access(cmd_path, X_OK) == 0)
			return (ft_free(paths), free(path), cmd_path);
		free(cmd_path);
		free(path);
		i++;
	}
	ft_free(paths);
	return (NULL);
}

int	count_options(char **arr, int i)
{
	int	count;

	count = 0;
	while (arr[i] && ft_strcmp(arr[i], "|"))
	{
		if ((!ft_strcmp(arr[i], "<") || !ft_strcmp(arr[i], "<<")
				|| !ft_strcmp(arr[i], ">")
				|| !ft_strcmp(arr[i], ">>")) && arr[i + 1])
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

void	get_commands(t_pipe *pipes, char **env, char **arr)
{
	char	**cmds;
	int		i;
	int		k;

	i = 0;
	while (pipes)
	{
		k = 0;
		cmds = (char **)malloc((count_options(arr, i) + 1) * sizeof (char *));
		while (arr[i] && ft_strcmp(arr[i], "|"))
		{
			if ((!ft_strcmp(arr[i], "<") || !ft_strcmp(arr[i], "<<")
					|| !ft_strcmp(arr[i], ">") || !ft_strcmp(arr[i], ">>")))
				i++;
			else
				cmds[k++] = remove_quotes(arr[i]);
			if (arr[i])
				i++;
		}
		cmds[k] = NULL;
		pipes->cmd = new_command(cmds, env);
		pipes = pipes->next;
		i++;
	}
}
