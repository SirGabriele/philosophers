/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:49:48 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/21 17:52:36 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_message_meal(t_context_ph *context_ph)
{
	long long	current;

	current = get_timestamp();
	printf("\e[41m%5lld ALL PHILO ATE ENOUGH\e[0m\n",
		(current - context_ph->time_start_sim) / 1000);
}

static void	print_message_death(t_context_ph *context_ph, int id)
{
	long long	current;

	current = get_timestamp();
	printf("\e[41m%5lld %3d died\e[0m\n",
		(current - context_ph->time_start_sim) / 1000, id + 1);
}

static int	check_meal_limit(t_context_ph *context_ph)
{
	if (context_ph->meal_limit == 0)
	{
		pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
		context_ph->mutex_meal_alert.data = 1;
		pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
		return (-1);
	}
	pthread_mutex_lock(&context_ph->mutex_meal_finished.mutex);
	if (context_ph->mutex_meal_finished.data >= context_ph->nb_philo)
	{
		pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
		context_ph->mutex_meal_alert.data = 1;
		pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
		print_message_meal(context_ph);
		return (-1);
	}
	pthread_mutex_unlock(&context_ph->mutex_meal_finished.mutex);
	return (0);
}

static int	check_death(t_context_ph *context_ph, int id)
{
	long long	lm;
	long long	ts;

	pthread_mutex_lock(&context_ph->thread[id].mutex_last_meal);
	lm = context_ph->thread[id].last_meal.tv_sec * 1000000;
	lm += context_ph->thread[id].last_meal.tv_usec;
	pthread_mutex_unlock(&context_ph->thread[id].mutex_last_meal);
	ts = get_timestamp();
	if (((ts - lm) / 1000) > context_ph->time_to_die)
	{
		pthread_mutex_lock(&context_ph->mutex_write);
		pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);
		context_ph->mutex_death_alert.data = 1;
		print_message_death(context_ph, id);
		pthread_mutex_unlock(&context_ph->mutex_write);
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
		return (-1);
	}
	return (0);
}

void	god_routine(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	lock_death_meal_alert(context_ph);
	while (context_ph->mutex_death_alert.data != 1
		&& context_ph->mutex_meal_alert.data != 1)
	{
		unlock_death_meal_alert(context_ph);
		if (check_death(context_ph, i) == -1
			|| check_meal_limit(context_ph) == -1)
		{
			lock_death_meal_alert(context_ph);
			break ;
		}
		i++;
		if (i == context_ph->nb_philo)
			i = 0;
		lock_death_meal_alert(context_ph);
	}
	unlock_death_meal_alert(context_ph);
}
