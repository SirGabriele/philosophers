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

void	ft_better_usleep(t_context_ph *context_ph, int usec)
{
	long long		start;

	start = get_timestamp();
	while (get_timestamp() - start <= usec)
	{
		pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);
		if (context_ph->meal_limit > 0)
			pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
		if (context_ph->mutex_death_alert.data == 1
			|| context_ph->mutex_meal_alert.data == 1)
		{
			pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
			if (context_ph->meal_limit > 0)
				pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
			return ;
		}
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
		if (context_ph->meal_limit > 0)
			pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
		usleep(10);
	}
}

void	print_message(t_context_ph *context_ph, int id, char *msg)
{
	long long	current;
	long long	start;

	current = get_timestamp();
	start = context_ph->time_start_sim.tv_sec * 1000000;
	start += context_ph->time_start_sim.tv_usec;
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);
	if (context_ph->meal_limit > 0)
		pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
	if (context_ph->mutex_death_alert.data == 1
		|| context_ph->mutex_meal_alert.data == 1)
	{
//		pthread_mutex_lock(&context_ph->mutex_write);
//		printf("Death | Meal limit detected\n");
//		pthread_mutex_unlock(&context_ph->mutex_write);
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
		if (context_ph->meal_limit > 0)
			pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
		return ;
	}
	pthread_mutex_lock(&context_ph->mutex_write);
	printf("%lld %d %s\n", ((current - start) / 1000), id + 1, msg);
	pthread_mutex_unlock(&context_ph->mutex_write);
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
	if (context_ph->meal_limit > 0)
		pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
}
