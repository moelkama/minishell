/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:38:39 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/14 14:30:42 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*findvar(char *str, int i)
{
	char	*ptr;
	int		count;
	int		j;

	count = 0;
	while (is_valid(str[i + count]))
		count++;
	ptr = (char *)malloc((count + 1) * sizeof(char ));
	if (!ptr)
		return (NULL);
	j = 0;
	while (j < count)
		ptr[j++] = str[i++];
	ptr[j] = '\0';
	return (ptr);
}

char	*get_var(char **env, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] == var[j])
			j++;
		if (!var[j] && env[i][j] == '=')
			return (&env[i][j + 1]);
		i++;
	}
	return (NULL);
}

int	with_vars(char *line, char **env)
{
	char	*ptr;
	int		count;
	int		q[2];

	count = 0;
	q[0] = 0;
	q[1] = 0;
	while (line && *line)
	{
		if (q[1] == 0 && *line == '$' && line[1] == '?')
		{
			count += 2;
			line++;
		}
		else if (q[1] == 0 && *line == '$' && is_valid(line[1]))
		{
			ptr = findvar(line, 1);
			count += ft_strlen(get_var(env, ptr)) - 1;
			line += ft_strlen(ptr);
			free(ptr);
		}
		count++;
		manage_quotes(line++, 0, q, q + 1);
	}
	return (count);
}

int	fill(char *line, char *new, char **env, int *i)
{
	char		*ptr;
	int			k;

	k = 0;
	if (line[*i + 1] == '?')
	{
		if (*g_status == -1)
			ptr = ft_itoa(258);
		else
			ptr = ft_itoa(WEXITSTATUS(*g_status));
		ft_strncopy(new, ptr, ft_nbrlen(WEXITSTATUS(*g_status)));
		k += ft_nbrlen(WEXITSTATUS(*g_status));
		free(ptr);
		(*i)++;
	}
	else if (is_valid(line[*i + 1]))
	{
		ptr = findvar(line, *i + 1);
		k = ft_strlen(get_var(env, ptr));
		ft_strncopy(new, get_var(env, ptr), k);
		(*i) += ft_strlen(ptr);
		free(ptr);
	}
	return (k);
}

char	*add_vars(char *line, char **env, int d, int s)
{
	char	*new;
	int		i;
	int		k;

	new = (char *)malloc((with_vars(line, env) + 1) * sizeof (char ));
	if (!new)
		return (NULL);
	k = 0;
	i = 0;
	while (line && line[i])
	{
		manage_quotes(line, i, &d, &s);
		if (is_exist(line, '|') < i && is_exist(line, '|') != -1)
			*g_status = 0;
		if (s == 0 && line[i] == '$' && ft_isnum(line[i + 1]))
			i++;
		else if (s == 0 && line[i] == '$' && is_valid(line[i + 1]))
			k += fill(line, &new[k], env, &i);
		else if (line[i] != '$' || (s == 1) || (!is_valid(line[i + 1])
				&& line[i + 1] != '"' && line[i + 1] != '\'')
			|| (line[i] == '$' && !is_valid(line[i + 1])))
			new[k++] = line[i];
		i++;
	}
	return (new[k] = '\0', new);
}
