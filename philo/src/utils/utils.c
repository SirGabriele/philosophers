/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:32:25 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/10 20:26:35 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

											//faire usleep par coups de 50 usec

void	ft_better_usleep(int usec)
{
	struct timeval	current_time;
	struct timeval	start_time;
	long double		start;
	long double		current;

	gettimeofday(&start_time, NULL);
	start = start_time.tv_sec * 1000000 + start_time.tv_usec;
	gettimeofday(&current_time, NULL);
	current = current_time.tv_sec * 1000000 + current_time.tv_usec;
	while (current - start <= usec)
	{
		gettimeofday(&current_time, NULL);
		current = current_time.tv_sec * 1000000 + current_time.tv_usec;
	}
}

void	*ft_calloc(size_t size, size_t nmemb)
{
	unsigned char	*tab;
	size_t			i;

	i = 0;
	if (size > 2147483647 || nmemb > 2147483647)
		return (NULL);
	tab = malloc(size * nmemb);
	if (tab == NULL)
		return (NULL);
	else if (nmemb * size > 2147483647)
		return (NULL);
	while (i < nmemb * size)
	{
		tab[i] = '\0';
		i++;
	}
	return ((void *)tab);
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
