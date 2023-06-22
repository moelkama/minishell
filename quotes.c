/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:52:47 by moelkama          #+#    #+#             */
/*   Updated: 2023/05/27 12:20:01 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *str, int fd, int endl)
{
	while (*str)
		write(fd, str++, 1);
	if (endl)
		write(fd, "\n", 1);
}

int	manage_quotes(char *line, int i, int *d, int *s)
{
	if (line[i] == '"' && *d == 0 && *s == 0)
		*d = 1;
	else if (line[i] == '"' && *d == 1 && *s == 0)
		*d = 0;
	else if (line[i] == 39 && *d == 0 && *s == 0)
		*s = 1;
	else if (line[i] == 39 && *d == 0 && *s == 1)
		*s = 0;
	else
		return (0);
	return (1);
}

int	whitout_qutes(char *str)
{
	int	count;
	int	d;
	int	s;
	int	i;

	count = 0;
	i = 0;
	d = 0;
	s = 0;
	while (str[i])
	{
		if (!manage_quotes(str, i, &d, &s))
			count++;
		i++;
	}
	return (count);
}

char	*remove_quotes(char *line)
{
	char	*new;
	int		len;
	int		i;
	int		d;
	int		s;

	d = 0;
	s = 0;
	i = 0;
	if (!line)
		return (NULL);
	len = whitout_qutes(line);
	new = (char *)malloc(((len + 1) * sizeof(char )));
	if (!new)
		return (NULL);
	while (line && *line)
	{
		if (!manage_quotes(line, 0, &d, &s))
			new[i++] = *line;
		line++;
	}
	new[i] = '\0';
	return (new);
}

int	quotes_error(char *line)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	while (line[i])
		manage_quotes(line, i++, &d, &s);
	if (s == 1)
		ft_putstr_fd("syntax error near unexpected token singlequote", 2, 1);
	else if (d == 1)
		ft_putstr_fd("syntax error near unexpected token doublequotes", 2, 1);
	else
		return (1);
	return (0);
}
