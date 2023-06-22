/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:09:07 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/15 19:51:48 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_env(char **env, t_list **ptr, int show)
{
	int			i;
	static int	j;
	t_list		*head;

	i = -1;
	j = 0;
	if (!(*ptr) && j == 0)
	{
		while (env[++i])
			get_var_key(env[i], ptr, 1);
		j++;
	}
	head = (*ptr);
	if (!check_if_exit(head, "OLDPWD"))
		get_var_key("OLDPWD=", ptr, 1);
	while (head && show == 1)
	{
		if (head->key && head->var)
			printf("%s=%s\n", head->var, head->key);
		head = head->next;
	}
}

void	ft_unset(char **unset, t_list **ptr, int show)
{
	int		i;
	int		j;

	i = 0;
	while (unset[++i])
	{
		if (!ft_check(unset[i]) || !ft_strcmp("_", unset[i]))
		{
			if (show == 1 && unset[i][0] != '_')
			{
				j = 1;
				ft_printf("unset: `%s': not a valid identifier\n", unset[i]);
			}
		}
		else
			ft_remove2(ptr, unset[i]);
	}
	if (unset[i] == NULL && j == 1)
		exit(1);
}

void	ft_changeoldpwd(t_list	*head, char *pwd, char *oldpwd)
{
	while (head)
	{
		if (ft_strcmp(head->var, "PWD") == 0)
		{
			if (head->key)
				free(head->key);
			head->key = ft_alloc(pwd);
		}
		else if (ft_strcmp(head->var, "OLDPWD") == 0 && pwd)
		{
			if (head->key)
				free(head->key);
			head->key = ft_alloc(oldpwd);
		}
		head = head->next;
	}
}

void	ft_cd(char *path, t_list **ptr, int show)
{
	t_list	*head;
	char	oldpwd[OPEN_MAX];
	char	pwd[OPEN_MAX];

	head = *ptr;
	if (!path)
		path = ft_find_var(*ptr, "HOME");
	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(path) == -1)
	{
		printerr(show, path);
		return ;
	}
	getcwd(pwd, sizeof(pwd));
	if (!(*ptr))
		return ;
	ft_changeoldpwd(head, pwd, oldpwd);
}
