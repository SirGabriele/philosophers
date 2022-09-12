/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:32:25 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 01:27:53 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*long long	get_timestamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000000 + current_time.tv_usec);
}*/

							//ajouter meal_cap
/*int	ft_better_usleep(t_context_ph *context_ph, int usec)
{
	long long		start;

	start = get_timestamp();
	while (get_timestamp() - start <= usec)
	{
		pthread_mutex_lock(&context_ph->mutex_death_alert->mutex);
		if (context_ph->mutex_death_alert->data == 1)
			return (-1); ;
		pthread_mutex_unlock(&context_ph->mutex_death_alert->mutex);
		usleep(50);
	}
	return (0);
}*/

int	ft_strlen_ignore_left_zeros(char *str)
{
	int	count;

	count = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0' && *str != '\0')
		str++;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
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
	int			sign;
	long int	res;

	sign = 1;
	res = 0;
	while (((*tab >= 9 && *tab <= 13) || *tab == 32) && *tab != '\0')
			tab++;
	if (*tab == '\0')
		return (-1);
	if (*tab == '-' || *tab == '+')
	{
		if (*tab == '-')
			sign = -sign;
		tab++;
	}
	while (*tab >= 48 && *tab <= 57)
	{
		res = res * 10 + (*tab - 48);
		tab++;
		if ((sign == 1 && res > 2147483647) || (sign == -1 && res > 2147483648))
			return (-1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	number;

	sign = 1;
	number = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == 45)
			sign = -sign;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		number = number * 10 + (*nptr - 48);
		nptr++;
	}
	return (sign * number);
}
