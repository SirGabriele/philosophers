/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:06:16 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/10 20:29:02 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

			//		add red_alert check in check_death

static int	check_death(t_context_ph *context_ph, int id)
{
	struct timeval	current_time;
	long long		current;
	long long		last_meal;

	if (context_ph->mutex_red_alert->data == 1)
		return (-1);
	gettimeofday(&current_time, NULL);
	current = current_time.tv_sec * 1000000 + current_time.tv_usec;
	last_meal = context_ph->thread[id].last_meal.tv_sec * 1000000;
	last_meal += context_ph->thread[id].last_meal.tv_usec;
	if (current - last_meal > context_ph->time_to_die * 1000)
	{
		pthread_mutex_lock(&context_ph->mutex_write->mutex);
		print_message(context_ph, id, "died");
		pthread_mutex_unlock(&context_ph->mutex_write->mutex);
		pthread_mutex_lock(&context_ph->mutex_red_alert->mutex);
		context_ph->mutex_red_alert->data = 1;
		pthread_mutex_unlock(&context_ph->mutex_red_alert->mutex);
		return (-1);
	}
	return (0);
}

static void	takes_forks_and_eats(t_context_ph *context_ph, int id)
{
	pthread_mutex_lock(&context_ph->mutex_fork[id].mutex);
	pthread_mutex_lock(&context_ph->mutex_write->mutex);
	print_message(context_ph, id, "has taken a fork");
	pthread_mutex_unlock(&context_ph->mutex_write->mutex);
	if (id == context_ph->nb_philo - 1 && context_ph->mutex_red_alert->data == 0)
		pthread_mutex_lock(&context_ph->mutex_fork[0].mutex);
	else if (context_ph->mutex_red_alert->data == 0)
		pthread_mutex_lock(&context_ph->mutex_fork[id + 1].mutex);
	gettimeofday(&context_ph->thread[id].last_meal, NULL);
	pthread_mutex_lock(&context_ph->mutex_write->mutex);
	print_message(context_ph, id, "has taken a fork");
	print_message(context_ph, id, "is eating");
	pthread_mutex_unlock(&context_ph->mutex_write->mutex);
	ft_better_usleep(context_ph, context_ph->time_to_eat * 1000);
	pthread_mutex_unlock(&context_ph->mutex_fork[id].mutex);
	if (id == context_ph->nb_philo - 1)
		pthread_mutex_unlock(&context_ph->mutex_fork[0].mutex);
	else
		pthread_mutex_unlock(&context_ph->mutex_fork[id + 1].mutex);
}

int	routine(t_context_ph *context_ph, int id)
{
	gettimeofday(&context_ph->thread[id].last_meal, NULL);
	while (1)
	{
		if (check_death(context_ph, id) == -1)
			return (-1);
		takes_forks_and_eats(context_ph, id);
		if (check_death(context_ph, id) == -1)
			return (-1);
		pthread_mutex_lock(&context_ph->mutex_write->mutex);
		print_message(context_ph, id, "is sleeping");
		pthread_mutex_unlock(&context_ph->mutex_write->mutex);
		ft_better_usleep(context_ph, context_ph->time_to_sleep * 1000);
		if (check_death(context_ph, id) == -1)
			return (-1);
		pthread_mutex_lock(&context_ph->mutex_write->mutex);
		print_message(context_ph, id, "is thinking");
		pthread_mutex_unlock(&context_ph->mutex_write->mutex);
	}
	return (0);
}
