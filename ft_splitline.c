/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:24:05 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/12 15:21:41 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count(char *s, int start, int len)
{
	if (len > ft_strlen(s) - start && start < ft_strlen(s))
		return (ft_strlen(s) - start);
	else if (len <= ft_strlen(s) - start && start < ft_strlen(s))
		return (len);
	return (0);
}

char	*returnstr(char *s, int start, int len)
{
	char	*str;
	int		index;

	if (!s)
		return (NULL);
	str = (char *)malloc((ft_count(s, start, len) + 1) * sizeof(char ));
	if (str)
	{
		index = 0;
		while (index < len && ft_count(s, start, len) && s[start])
			str[index++] = s[start++];
		str[index] = '\0';
		return (str);
	}
	return (NULL);
}

int	ft_count_strs(char *str, char *c)
{
	int	count_strs;
	int	d;
	int	s;
	int	m;

	d = 0;
	s = 0;
	count_strs = 0;
	while (str && *str)
	{
		while (*str && (s == 0 && d == 0 && if_exist(c, *str)))
			str++;
		m = 0;
		while (*str && (s == 1 || d == 1 || !if_exist(c, *str)))
		{
			manage_quotes(str, 0, &d, &s);
			m = 1;
			str++;
		}
		if (m == 1)
			count_strs++;
	}
	return (count_strs);
}

char	**ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(char *str, char *c)
{
	char	**strs;
	char	*ptr;
	int		tab[2];
	int		d;
	int		s;

	tab[1] = ft_count_strs(str, c);
	strs = (char **)malloc((tab[1] + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs[tab[1]] = NULL;
	tab[0] = 0;
	s = 0;
	d = 0;
	while (tab[0] < tab[1])
	{
		while (*str && if_exist(c, *str))
			str++;
		ptr = str;
		while (*str && (d == 1 || s == 1 || !if_exist(c, *str)))
			manage_quotes(str++, 0, &d, &s);
		strs[tab[0]++] = returnstr(ptr, 0, str - ptr);
	}
	return (strs);
}
