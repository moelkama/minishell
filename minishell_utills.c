/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:01:08 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/15 19:00:53 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_var_key(char *env, t_list **ptr, int sort)
{
	int		i;
	int		j;
	char	*var;
	char	*key;

	i = 0;
	j = -1;
	while (env[i] != '=')
		i++;
	var = malloc(i + 1);
	while (++j < i && env[j] != '+')
		var[j] = env[j];
	var[j] = '\0';
	key = malloc(ft_strlen(env) - i + 1);
	j = 0;
	while (env[++i])
		key[j++] = env[i];
	key[j] = '\0';
	if (ft_strcmp(var, "OLDPWD"))
		ft_lstadd_back(ptr, ft_lstnew(key, var, sort));
	else
	{
		ft_lstadd_back(ptr, ft_lstnew(NULL, var, sort));
		free(key);
	}
}

void	ft_sortlist(t_list *ptr)
{
	t_list	*head;
	char	*tmp1;
	char	*tmp2;

	while (ptr)
	{
		head = ptr->next;
		while (head)
		{
			if (ft_strcmp(ptr->var, head->var) > 0)
			{
				tmp1 = head->var;
				tmp2 = head->key;
				head->var = ptr->var;
				head->key = ptr->key;
				ptr->var = tmp1;
				ptr->key = tmp2;
			}
			head = head->next;
		}
		ptr = ptr->next;
	}
}

int	ft_check_echo(char *option)
{
	int	i;

	if (!option)
		return (0);
	if (option[0] != '-')
		return (0);
	i = 0;
	while (option[++i])
		if (option[i] != 'n')
			return (0);
	if (i == 1)
		return (0);
	return (1);
}

char	*ft_delete_dirname(char *str)
{
	int		j;
	int		i;
	char	*newpath;

	if (!str)
		return (NULL);
	j = ft_strlen(str) - 1;
	while (j > 0 && str[j] != '/')
		j--;
	newpath = malloc(j + 1);
	i = -1;
	while (++i < j)
		newpath[i] = str[i];
	newpath[i] = '\0';
	if (str)
		free(str);
	return (newpath);
}

void	ft_remove2(t_list **ptr, char *unset)
{
	t_list	*p;
	t_list	*rm;

	if ((*ptr) && ft_strcmp((*ptr)->var, unset) == 0)
		ft_remove(ptr);
	else if ((*ptr))
	{
		p = (*ptr);
		while (p)
		{
			if (p->next && ft_strcmp(p->next->var, unset) == 0)
			{
				rm = p->next;
				p->next = p->next->next;
				free(rm->key);
				free(rm->var);
				free(rm);
				break ;
			}
			p = p->next;
		}
	}
}
