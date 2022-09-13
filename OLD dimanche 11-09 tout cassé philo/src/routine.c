/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:11:34 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/11 20:50:37 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death_and_meal_cap(t_context_ph *context_ph, int id)
{
	long long	current;
	long long	last_meal;


	pthread_mutex_lock(&context_ph->mutex_red_alert->mutex);
		if (context_ph->mutex_red_alert->data == 1)
			return (-1);
	pthread_mutex_unlock(&context_ph->mutex_red_alert->mutex);
	last_meal = context_ph->thread[id].last_meal.tv_sec * 1000000;
	last_meal += context_ph->thread[id].last_meal.tv_usec;
	current = get_timestamp();
	if (current - last_meal > context_ph->time_to_die)
	{
		pthread_mutex_lock(&context_ph->mutex_red_alert->mutex);
		context_ph->mutex_red_alert->data = 1;
		pthread_mutex_unlock(&context_ph->mutex_red_alert->mutex);
		print_message(context_ph, id, "died");
		return (-1);
	}
	return (0);
}

static int	takes_forks_and_eats(t_context_ph *context_ph, int id)
{
	if (check_death_and_meal_cap(context_ph, id) == -1)
		return (-1);
	pthread_mutex_lock(&context_ph->mutex_fork[id].mutex);
	print_message(context_ph, id, "has taken a fork");
	if (id == context_ph->nb_philo - 1)
		pthread_mutex_lock(&context_ph->mutex_fork[0].mutex);
	else
		pthread_mutex_lock(&context_ph->mutex_fork[id + 1].mutex);
	print_message(context_ph, id, "has taken a fork");
	print_message(context_ph, id, "is eating");
	gettimeofday(&context_ph->thread[id].last_meal, NULL);

	long long lm = context_ph->thread[id].last_meal.tv_sec * 1000000 + context_ph->thread[id].last_meal.tv_usec; 
	printf("Last meal of %d value = %lld\n", id + 1, lm);/////

	pthread_mutex_unlock(&context_ph->mutex_fork[id].mutex);
	if (id == context_ph->nb_philo - 1)
		pthread_mutex_unlock(&context_ph->mutex_fork[0].mutex);
	else
		pthread_mutex_unlock(&context_ph->mutex_fork[id + 1].mutex);
	if (ft_better_usleep(context_ph, context_ph->time_to_eat * 1000) == -1)
		return (-1);
	return (0);
}

int	routine(t_context_ph *context_ph, int id)
{
	gettimeofday(&context_ph->thread[id].last_meal, NULL);
	while (1)
	{
		if (takes_forks_and_eats(context_ph, id) == -1)
			return (-1);
		if (check_death_and_meal_cap(context_ph, id) == -1)
			return (-1);
		print_message(context_ph, id, "is sleeping");
		if (ft_better_usleep(context_ph, context_ph->time_to_sleep * 1000) == -1)
			return (-1);
		if (check_death_and_meal_cap(context_ph, id) == -1)
			return (-1);
		print_message(context_ph, id, "is thinking");
	}
	return (0);
}
