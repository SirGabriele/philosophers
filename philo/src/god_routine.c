/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:49:48 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 16:15:03 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*static void	print_message_god(t_context_ph *context_ph, int id, char *msg)
{

}*/

static void	check_meal_limit(t_context_ph *context_ph)
{
	pthread_mutex_lock(&context_ph->mutex_meal_finished.mutex);
	if (context_ph->mutex_meal_finished.data >= context_ph->nb_philo)
	{
					pthread_mutex_lock(&context_ph->mutex_write);
					printf("All philosophers ate the required amount of times = %d\n", context_ph->mutex_meal_finished.data);
					pthread_mutex_unlock(&context_ph->mutex_write);
		pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
		context_ph->mutex_meal_alert.data = 1;
		pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
	}
	pthread_mutex_unlock(&context_ph->mutex_meal_finished.mutex);
}

/*static void	check_death(t_context_ph *context_ph, int id)
{

}*/

void	god_routine(t_context_ph *context_ph)
{
	int	i;
	
	i = 0;
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);
	if (context_ph->meal_limit > 0)
		pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
	while (/*context_ph->mutex_death_alert.data != 1
		&& */context_ph->mutex_meal_alert.data != 1)
	{
				pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
				if (context_ph->meal_limit > 0)
					pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
		if (context_ph->meal_limit > 0)
			check_meal_limit(context_ph);
		i++;
		if (i == context_ph->nb_philo - 1)
			i = 0;
				pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);
				if (context_ph->meal_limit > 0)
					pthread_mutex_lock(&context_ph->mutex_meal_alert.mutex);
	}
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
	if (context_ph->meal_limit > 0)
		pthread_mutex_unlock(&context_ph->mutex_meal_alert.mutex);
}
