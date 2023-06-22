/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:27:57 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/14 18:16:36 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **str, char *option)
{
	int	i;

	i = 1;
	while (ft_check_echo(str[i]))
		i++;
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!ft_check_echo(option))
		write(1, "\n", 1);
}

int	ft_check_unset(char *unset)
{
	if ((!ft_isalpha(unset[0]) && unset[0] != '_'))
		return (1);
	if (!(ft_isalpha(unset[ft_strlen(unset) - 1]))
		&& !(ft_isnum(unset[ft_strlen(unset) - 1]))
		&& unset[ft_strlen(unset) - 1] != '_')
		return (1);
	return (0);
}

int	check_if_exit(t_list *ptr, char *str)
{
	while (ptr)
	{
		if (!ft_strcmp(ptr->var, str))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

char	*ft_find_var(t_list	*ptr, char *path)
{
	t_list	*home;

	if (!ptr)
		return (NULL);
	if (!ft_strcmp(path, "."))
		path = "PWD";
	home = ptr;
	while (home)
	{
		if (ft_strcmp(home->var, path) == 0)
			return (home->key);
		home = home->next;
	}
	return (NULL);
}

void	wait_checksignal(int *std)
{
	dup2(std[0], 0);
	dup2(std[1], 1);
	close(std[0]);
	close(std[1]);
	waitpid(std[2], g_status, 0);
	while (wait(NULL) != -1)
		;
	ft_signals(*g_status);
}
