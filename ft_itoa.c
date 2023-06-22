/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:05:52 by moelkama          #+#    #+#             */
/*   Updated: 2023/05/27 12:19:08 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_10_len(long nb, int form)
{
	int		len;
	int		k;

	len = 1;
	k = 1;
	if (nb < 0)
		len++;
	while (nb / 10 != 0)
	{
		k *= 10;
		len++;
		nb /= 10;
	}
	if (form == 0)
		return (k);
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	long		nb;
	int			k;
	int			len;
	int			i;

	nb = n;
	k = ft_10_len(nb, 0);
	len = ft_10_len(nb, 1);
	if (nb < 0)
		nb *= -1;
	str = (char *)malloc((len + 1) * sizeof(char ));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
		str[i++] = '-';
	while (k >= 1)
	{
		str[i++] = nb / k + 48;
		nb %= k;
		k /= 10;
	}
	str[i] = '\0';
	return (str);
}
