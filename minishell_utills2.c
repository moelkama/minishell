/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:37:07 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/14 18:07:25 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(char **ptr)
{
	int	i;

	i = -1;
	if (!ptr)
		return ;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

int	ft_lstsize_pipe(t_pipe *pipe)
{
	int	i;

	i = 0;
	if (!pipe)
		return (0);
	while (pipe)
	{
		i++;
		pipe = pipe->next;
	}
	return (i);
}

void	printerr(int show, char *path)
{
	if (show == 1)
	{
		if (path && path[0] != '\0')
			ft_printf("cd : %s : no such file or directory\n", path);
		else if (!path)
			write(2, "cd: HOME not set\n", 17);
		exit(1);
	}
}

void	ft_remove(t_list **ptr)
{
	t_list	*rm;

	rm = (*ptr);
	*ptr = (*ptr)->next;
	free(rm->key);
	free(rm->var);
	free(rm);
}
