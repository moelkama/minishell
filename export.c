/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:42:09 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/15 20:17:47 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_give_key(char *str)
{
	int		i;
	int		j;
	char	*s1;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	s1 = malloc(ft_strlen(str) - i);
	while (str[++i])
		s1[j++] = str[i];
	s1[j] = '\0';
	return (s1);
}

int	ft_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_add_or_create(char *export, t_list **ptr, int show)
{
	t_list	*head;
	char	*var;

	head = (*ptr);
	var = ft_return_str(export);
	if (!ft_check(var))
	{
		if (show == 1)
		{
			ft_printf("export : `%s': not a valid identifier\n", export);
			exit (1);
		}
		else
		{
			free(var);
			return ;
		}
	}
	add_or_create2(head, var, ptr, export);
	free(var);
}

void	ft_export2(char **export, int show, t_list **ptr)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (export[++i])
	{
		str = ft_return_str(export[i]);
		if (ft_check_export(export[i]) == 2
			|| ft_check_export(export[i]) == 1)
			ft_add_or_create(export[i], ptr, show);
		else if ((ft_check_export(export[i]) == -1 || !ft_check(export[i])))
		{
			if (show == 1)
			{
				ft_printf("export : `%s': not a valid identifier\n", export[i]);
				j = 1;
			}
		}
		else if (ft_check_ifadd(ptr, str))
			ft_lstadd_back(ptr, ft_lstnew(NULL, ft_alloc(export[i]), 0));
		free(str);
	}
	if (j == 1 && export[i] == NULL)
		exit(1);
}

void	ft_export(char **export, t_list **ptr, int show)
{
	int		i;
	int		j;
	t_list	*last;

	i = 0;
	j = 0;
	last = (*ptr);
	if (!export[1] && show == 1)
	{
		ft_sortlist(last);
		while (last)
		{
			if (last->key)
				printf("declare -x %s=\"%s\"\n", last->var, last->key);
			else
				printf("declare -x %s\n", last->var);
			last = last->next;
		}
	}
	else
		ft_export2(export, show, ptr);
}
