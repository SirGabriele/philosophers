/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:39:45 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 19:00:35 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_timestamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000000 + current_time.tv_usec);
}

int	ft_better_usleep(t_context_ph *context_ph, int usec)
{
	long long		start;

	lock_death_and_meal_mutex(context_ph);
	if (context_ph->mutex_death_alert.data == 1
		|| context_ph->mutex_meal_alert.data == 1)
	{
		unlock_death_and_meal_mutex(context_ph);
		return (-1);
	}
	unlock_death_and_meal_mutex(context_ph);
	start = get_timestamp();
	while (get_timestamp() - start <= usec)
	{
		lock_death_and_meal_mutex(context_ph);
		if (context_ph->mutex_death_alert.data == 1
			|| context_ph->mutex_meal_alert.data == 1)
		{
			unlock_death_and_meal_mutex(context_ph);
			return (-1);
		}
		unlock_death_and_meal_mutex(context_ph);
		usleep(50);
	}
	return (0);
}

void	print_message(t_context_ph *context_ph, int id, char *msg)
{
	long long	current;
	long long	start;

	current = get_timestamp();
	start = context_ph->time_start_sim.tv_sec * 1000000;
	start += context_ph->time_start_sim.tv_usec;
	lock_death_and_meal_mutex(context_ph);
	if (context_ph->mutex_death_alert.data == 1
		|| context_ph->mutex_meal_alert.data == 1)
	{
		unlock_death_and_meal_mutex(context_ph);
		return ;
	}
	unlock_death_and_meal_mutex(context_ph);
	pthread_mutex_lock(&context_ph->mutex_write);
	printf("%lld %d %s\n", ((current - start) / 1000), id + 1, msg);
	pthread_mutex_unlock(&context_ph->mutex_write);
}

void	unlock_death_and_meal_mutex(t_context_ph *context_ph)
{
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
	if (context_ph->meal_limit > 0)
	{
		pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
		pthread_mutex_unlock(&context_ph->mutex_meal_finished.mutex);
	}
}

void	lock_death_and_meal_mutex(t_context_ph *context_ph)
{
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);
	if (context_ph->meal_limit > 0)
	{
		pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
		pthread_mutex_lock(&context_ph->mutex_meal_finished.mutex);
	}
}
