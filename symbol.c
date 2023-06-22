/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:25:13 by moelkama          #+#    #+#             */
/*   Updated: 2023/05/27 12:20:06 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spacex(char *line, int i, char *sp)
{
	int	len;
	int	count;

	len = ft_strlen(sp);
	count = 0;
	if (i > 0 && line[i - 1] != ' ')
		count++;
	if (line[i + 2] && line[i + 2] != ' ')
		count++;
	count += len - 1;
	return (count);
}

int	count_symbol(char *line)
{
	int	count;
	int	d;
	int	s;
	int	i;

	count = 0;
	d = 0;
	s = 0;
	i = 0;
	while (line[i])
	{
		manage_quotes(line, i, &d, &s);
		if (d == 0 && s == 0 && (!ft_strncmp(&line[i], "<<", 2)
				|| !ft_strncmp(&line[i], ">>", 2)))
			count += spacex(line, i++, "<<");
		else if (d == 0 && s == 0 && (line[i] == '<' || line[i] == '<'))
			count += spacex(line, i, "<");
		i++;
		count++;
	}
	return (count);
}

int	ft_cat(char *line, char *new, char *sp, int i)
{
	int	len;
	int	j;

	len = 0;
	j = 0;
	if (i > 0 && line[i - 1] != ' ')
		new[j++] = ' ';
	while (sp[len])
		new[j++] = sp[len++];
	if (line[i + len] && line[i + len] != ' ')
		new[j++] = ' ';
	return (j);
}

char	*manage_symbol(char *line)
{
	char	*new;
	int		q[2];
	int		i[2];

	new = (char *)malloc((count_symbol(line) + 1) * sizeof(char ));
	q[0] = 0;
	q[1] = 0;
	i[0] = 0;
	i[1] = 0;
	while (line[i[0]])
	{
		manage_quotes(line, *i, q, &q[1]);
		if (*q == 0 && q[1] == 0 && !ft_strncmp(&line[*i], "<<", 2))
			i[1] += ft_cat(line, &new[i[1]], "<<", i[0]++);
		else if (*q == 0 && q[1] == 0 && !ft_strncmp(&line[*i], ">>", 2))
			i[1] += ft_cat(line, &new[i[1]], ">>", i[0]++);
		else if (*q == 0 && q[1] == 0 && line[*i] == '<')
			i[1] += ft_cat(line, &new[i[1]], "<", *i);
		else if (*q == 0 && q[1] == 0 && line[*i] == '>')
			i[1] += ft_cat(line, &new[i[1]], ">", *i);
		else
			new[i[1]++] = line[i[0]];
		i[0]++;
	}
	return (new[i[1]] = '\0', new);
}

int	symbol_error(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], "<<", 2) && (!arr[i + 1]
				|| is_exist("<|>", arr[i + 1][0]) != -1))
			return (ft_putstr_fd("syntax error symbol!", 2, 1), 0);
		else if (!ft_strncmp(arr[i], "<", 1) && (!arr[i + 1]
				|| is_exist("<|>", arr[i + 1][0]) != -1))
			return (ft_putstr_fd("syntax error symbol!", 2, 1), 0);
		else if (!ft_strncmp(arr[i], ">>", 2) && (!arr[i + 1]
				|| is_exist("<|>", arr[i + 1][0]) != -1))
			return (ft_putstr_fd("syntax error symbol!", 2, 1), 0);
		else if (!ft_strncmp(arr[i], ">", 1) && (!arr[i + 1]
				|| is_exist("<|>", arr[i + 1][0]) != -1))
			return (ft_putstr_fd("syntax error symbol!", 2, 1), 0);
		i++;
	}
	return (1);
}
