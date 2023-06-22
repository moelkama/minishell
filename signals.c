/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:28:39 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/20 17:40:26 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_alloc(char *str)
{
	int		i;
	char	*str_ret;

	if (!str)
		return (NULL);
	str_ret = malloc(ft_strlen(str) + 1);
	i = -1;
	while (str[++i])
		str_ret[i] = str[i];
	str_ret[i] = '\0';
	return (str_ret);
}

void	handel_ctrlc(int sig)
{
	(void)sig;
	if (g_status[1] == 3)
		printf("\n");
	if (g_status[1] != 0)
		return ;
	printf("\n");
	*g_status = 256;
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	long	rs;
	int		s;
	int		i;

	s = 1;
	i = 0;
	rs = 0;
	if (str[i] == '\0')
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rs = rs * 10 + (str[i] - 48);
		if (rs > 9223372036854775807 && s == 1)
			return (-1);
		if (rs > 9223372036854775807 && s == -1)
			return (0);
		i++;
	}
	return (s * rs);
}
