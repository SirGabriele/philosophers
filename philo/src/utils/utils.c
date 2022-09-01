/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:32:25 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/01 16:29:28 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		*(char *)ptr = c;
		ptr++;
		i++;
	}
	return (s);
}

int	is_an_int(char *tab)
{
	int			i;
	int			sign;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (((tab[i] >= 9 && tab[i] <= 13) || tab[i] == 32) && tab[i] != '\0')
			i++;
	if (tab[i] == '\0')
		return (1);
	if (tab[i] == 45)
	{
		sign = -sign;
		i++;
	}
	while (tab[i] >= 48 && tab[i] <= 57)
	{
		res = res * 10 + (tab[i] - 48);
		i++;
		if ((sign == 1 && res > 2147483647) || (sign == -1 && res > 2147483648))
			return (1);
	}
	return (0);
}

long int	ft_atol(const char *nptr)
{
	int			i;
	int			sign;
	long int	number;

	i = 0;
	sign = 1;
	number = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign = -sign;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		number = number * 10 + (nptr[i] - 48);
		i++;
	}
	return (sign * number);
}