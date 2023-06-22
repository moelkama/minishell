/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:53:51 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/15 14:32:35 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_alloction(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	i = -1;
	while (s1 && s1[++i])
		str[i] = s1[i];
	str[i++] = '=';
	j = -1;
	while (s2 && s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	return (str);
}

void	ft_signals(int h)
{
	if (WIFSIGNALED(h))
	{
		if (WTERMSIG(h) == 3)
		{
			write(1, "Quit: 3\n", 8);
			*g_status = 33536;
		}
		else if (WTERMSIG(h) == 2)
		{
			if (g_status[1] == 1)
			{
				*g_status = 33280;
			}
			else
				*g_status = 256;
		}
	}
	g_status[1] = 0;
}

void	ft_puterror(char *cmd, char *cmd1)
{
	if (*cmd == '\0')
	{
		write(2, " : command not found\n", 21);
		exit (127);
	}
	if (opendir(cmd1))
	{
		ft_printf("%s : is a directory\n", cmd1);
		exit (126);
	}
}

int	ft_check_builtin(char *cmd, char *cmd1)
{
	if (!cmd || !cmd1)
		return (0);
	if (!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd1, "unset") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd1, "export")
		|| !ft_strcmp(cmd1, "exit"))
		return (1);
	return (0);
}

char	**ft_change_type(t_list *ptr)
{
	int		i;
	char	**envp;
	t_list	*head;

	head = ptr;
	i = 0;
	envp = malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	while (head)
	{
		if (head->var && head->key)
			envp[i++] = ft_alloction(head->var, head->key);
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}
