/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:30:39 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/16 12:51:28 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_return_str(char	*str)
{
	int		j;
	int		i;
	char	*newpath;

	j = 0;
	while (str[j])
	{
		if (str[j] == '=' || (str[j] == '+'
				&& str[j + 1] != '+' && str[j + 1] == '='))
			break ;
		j++;
	}
	newpath = malloc(j + 1);
	i = -1;
	while (++i < j)
		newpath[i] = str[i];
	newpath[i] = '\0';
	return (newpath);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (s2[i] != '=')
		i++;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) - i + 1);
	j = 0;
	while (*s1 && s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	return (str);
}

int	ft_check_export(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (-2);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	while (str[++i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (2);
		else if (str[i] == '=')
		{
			if (!ft_isalpha(str[i - 1]) && !ft_isnum(str[i - 1])
				&& str[i - 1] != '_')
				return (-1);
			return (1);
		}
	}
	return (0);
}

int	ft_check_ifadd(t_list **ptr, char *str)
{
	t_list	*head;

	head = (*ptr);
	while (head)
	{
		if (ft_strcmp(str, head->var) == 0)
			return (0);
		head = head->next;
	}
	return (1);
}

void	add_or_create2(t_list *head, char *var, t_list **ptr, char *export)
{
	char	*str;

	while (head && !ft_check_ifadd(ptr, var))
	{
		if (ft_strcmp(var, head->var) == 0)
		{
			str = head->key;
			if (ft_check_export(export) == 2 && head->key)
				head->key = ft_strcat(head->key, export);
			else
				head->key = ft_give_key(export);
			free(str);
			return ;
		}
		head = head->next;
	}
	if (ft_check_export(export) == 2)
		get_var_key(export, ptr, 0);
	else if (export && ft_check_export(export) == 1)
		get_var_key(export, ptr, 0);
}
