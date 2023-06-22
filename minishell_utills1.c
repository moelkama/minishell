/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:37:55 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/14 21:20:30 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(void)
{
	char	pwd[OPEN_MAX];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

void	ft_printf(char *str, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '%' && str[i + 1] == 's')
		{
			j = 0;
			write(2, s, ft_strlen(s));
			i += 2;
		}
		else
		{
			write(2, &str[i], 1);
			i++;
		}
	}
}

void	ft_exit2(int i, char **ext, int show)
{
	while (ext[i])
		i++;
	if (i > 2)
	{
		if (show == 1)
			write(2, "exit\n", 5);
		if (show == 0)
		{
			write(2, "exit: too many arguments\n", 25);
			exit(1);
		}
		*g_status = 256;
		return ;
	}
	if (show == 1)
		write(1, "exit\n", 5);
	exit(ft_atoi(ext[1]));
}

void	ft_exit(char **ext, int show)
{
	int	i;

	if (!ext[1])
	{
		if (show == 1)
			write(1, "exit\n", 5);
		exit(WEXITSTATUS(*g_status));
	}
	i = -1;
	if (ext[1][0] == '-' || ext[1][0] == '+')
		i++;
	while (ext[1][++i])
	{
		if (!(ext[1][i] >= '0' && ext[1][i] <= '9') && ext[1][i] != ' ')
		{
			if (show == 1)
				write(2, "exit\n", 5);
			if (show == 0)
				ft_printf("exit: %s: numeric argument required\n", ext[1]);
			exit(255);
		}
	}
	i = 1;
	ft_exit2(i, ext, show);
}

char	*to_lowor(char *s1)
{
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	str = malloc(ft_strlen(s1) + 1);
	while (s1[i])
	{
		if (s1[i] >= 'A' && s1[i] <= 'Z')
			str[i] = s1[i] + 32;
		else
			str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
