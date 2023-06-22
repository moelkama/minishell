/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:38:12 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/12 13:30:24 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	count_pipe(char *line)
{
	int	count;
	int	d;
	int	s;
	int	i;

	count = 0;
	d = 0;
	s = 0;
	i = -1;
	while (line[++i])
	{
		manage_quotes(line, i, &d, &s);
		if (d == 0 && s == 0 && line[i] == '|')
		{
			if (i > 0 && line[i - 1] != ' ')
				count++;
			if (line[i + 1] && line[i + 1] != ' ')
				count++;
		}
		count++;
	}
	return (count);
}

char	*manage_pipe(char *line)
{
	char	*new;
	int		d;
	int		s;
	int		i;
	int		j;

	new = (char *)malloc((count_pipe(line) + 1) * sizeof (char ));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	d = 0;
	s = 0;
	while (line[i])
	{
		manage_quotes(line, i, &d, &s);
		if (d == 0 && s == 0 && line[i] == '|')
			j += ft_cat(line, &new[j], "|", i++);
		else
			new[j++] = line[i++];
	}
	return (new[j] = '\0', new);
}

int	pipe_error(char **words)
{
	int		i;

	i = 0;
	while (words[i])
	{
		if (i == 0 && !ft_strncmp(words[i], "|", 1))
			break ;
		else if (!ft_strncmp(words[i], "|", 1) && !words[i + 1])
			break ;
		else if (!ft_strncmp(words[i], "|", 1)
			&& !ft_strncmp(words[i + 1], "|", 1))
			break ;
		i++;
	}
	if (words[i])
	{
		ft_putstr_fd("syntax error near unexpected token `|'", 2, 1);
		return (*g_status = 258, 0);
	}
	return (1);
}

t_pipe	*get_pipes(char *line, char **env)
{
	t_pipe	*pipe;
	char	**arr;
	char	*new;
	char	*swp;

	new = manage_pipe(line);
	swp = new;
	new = manage_symbol(new);
	free(swp);
	arr = ft_split(new, " \t");
	if (!quotes_error(new) || !pipe_error(arr) || !symbol_error(arr))
		return (*g_status = -1, free(new), ft_free(arr), NULL);
	pipe = here_doc(arr, env);
	if (g_status[2] == 1)
		return (free(new), ft_free(arr), free_pipes(&pipe, NULL, NULL), NULL);
	get_files(pipe, arr, env, -1);
	swp = new;
	new = add_vars(new, env, 0, 0);
	free(swp);
	ft_free(arr);
	arr = ft_split(new, " \t");
	get_commands(pipe, env, arr);
	free(new);
	ft_free(arr);
	return (pipe);
}
