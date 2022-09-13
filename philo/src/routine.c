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

static int	check_death_and_meal_alert(t_context_ph *context_ph)
{
	lock_death_and_meal_mutex(context_ph);
	if (context_ph->mutex_death_alert.data == 1
		|| context_ph->mutex_meal_alert.data == 1)
	{
		unlock_death_and_meal_mutex(context_ph);
		return (-1);
	}
	unlock_death_and_meal_mutex(context_ph);
	return (0);
}

static int	takes_forks_and_eats(t_context_ph *context_ph, int id)
{
	pthread_mutex_lock(&context_ph->thread[id].mutex_fork);
	print_message(context_ph, id, "has taken a fork");
	if (id == context_ph->nb_philo - 1)
		pthread_mutex_lock(&context_ph->thread[0].mutex_fork);
	else
		pthread_mutex_lock(&context_ph->thread[id + 1].mutex_fork);
	print_message(context_ph, id, "has taken a fork");
	print_message(context_ph, id, "is eating");
	context_ph->thread[id].meal_counter++;
	pthread_mutex_lock(&context_ph->thread[id].mutex_last_meal);
	gettimeofday(&context_ph->thread[id].last_meal, NULL);
	pthread_mutex_unlock(&context_ph->thread[id].mutex_last_meal);
	ft_better_usleep(context_ph, context_ph->time_to_eat * 1000);
	if (context_ph->thread[id].meal_counter == context_ph->meal_limit)
	{
		pthread_mutex_lock(&context_ph->mutex_meal_finished.mutex);
		context_ph->mutex_meal_finished.data++;
		pthread_mutex_unlock(&context_ph->mutex_meal_finished.mutex);
	}
	pthread_mutex_unlock(&context_ph->thread[id].mutex_fork);
	if (id == context_ph->nb_philo - 1)
		pthread_mutex_unlock(&context_ph->thread[0].mutex_fork);
	else
		pthread_mutex_unlock(&context_ph->thread[id + 1].mutex_fork);
	return (0);
}

void	routine(t_context_ph *context_ph, int id)
{

	pthread_mutex_lock(&context_ph->thread[id].mutex_last_meal);
	gettimeofday(&context_ph->thread[id].last_meal, NULL);
	pthread_mutex_unlock(&context_ph->thread[id].mutex_last_meal);
	lock_death_and_meal_mutex(context_ph);
	while (context_ph->mutex_death_alert.data != 1
		&& context_ph->mutex_meal_alert.data != 1)
	{
		unlock_death_and_meal_mutex(context_ph);
		takes_forks_and_eats(context_ph, id);
		if (check_death_and_meal_alert(context_ph) == -1)
			return ;
		print_message(context_ph, id, "is sleeping");
		ft_better_usleep(context_ph, context_ph->time_to_sleep * 1000);
		print_message(context_ph, id, "is thinking");
		lock_death_and_meal_mutex(context_ph);
	}
	unlock_death_and_meal_mutex(context_ph);
}
