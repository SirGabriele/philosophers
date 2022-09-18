/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 01:11:36 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 21:37:13 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	update_last_meal_timer(t_context_ph *context_ph, int id)
{
	pthread_mutex_lock(&context_ph->thread[id].mutex_last_meal);
	gettimeofday(&context_ph->thread[id].last_meal, NULL);
	pthread_mutex_unlock(&context_ph->thread[id].mutex_last_meal);
}

/*static void	manage_meal_counters(t_context_ph *context_ph, int id)
{
	if (context_ph->meal_limit > 0)
	{
		context_ph->thread[id].meal_counter++;
		if (context_ph->thread[id].meal_counter == context_ph->meal_limit)
		{
			pthread_mutex_lock(&context_ph->mutex_meal_finished.mutex);
			context_ph->mutex_meal_finished.data++;
			pthread_mutex_unlock(&context_ph->mutex_meal_finished.mutex);
		}
	}
}*/

/*static void	takes_forks_and_eats(t_context_ph *context_ph, int id)
{
	pthread_mutex_lock(&context_ph->thread[id].mutex_fork);
	print_message(context_ph, id, "has taken a fork");
	if (id == context_ph->nb_philo - 1)
		pthread_mutex_lock(&context_ph->thread[0].mutex_fork);
	else
		pthread_mutex_lock(&context_ph->thread[id + 1].mutex_fork);
	print_message(context_ph, id, "has taken a fork");
	print_message(context_ph, id, "is eating");
	update_last_meal_timer(context_ph, id);
	ft_better_usleep(context_ph, context_ph->time_to_eat * 1000);
	manage_meal_counters(context_ph, id);
	pthread_mutex_unlock(&context_ph->thread[id].mutex_fork);
	if (id == context_ph->nb_philo - 1)
		pthread_mutex_unlock(&context_ph->thread[0].mutex_fork);
	else
		pthread_mutex_unlock(&context_ph->thread[id + 1].mutex_fork);
}*/

void	routine(t_context_ph *context_ph, int id)
{
	update_last_meal_timer(context_ph, id);
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);
	if (context_ph->meal_limit > 0)
		pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
	while (context_ph->mutex_death_alert.data != 1
		&& context_ph->mutex_meal_alert.data != 1)
	{
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
		if (context_ph->meal_limit > 0)
			pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
		print_message(context_ph, id, "is thinking");
		takes_forks_and_eats(context_ph, id);
/*		print_message(context_ph, id, "is sleeping");
		ft_better_usleep(context_ph, context_ph->time_to_sleep * 1000);*/
		pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);
		if (context_ph->meal_limit > 0)
			pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
	}
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
	if (context_ph->meal_limit > 0)
		pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
}
