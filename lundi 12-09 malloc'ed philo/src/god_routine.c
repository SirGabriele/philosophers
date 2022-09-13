/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 22:20:08 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/10 22:32:46 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	god_routine(t_context_ph *context_ph)
{
/*	int				id;
	long double		current;
	long double		last_meal;

	current = get_timestamp(); 
	id = 0;
	while (1)
	{
		last_meal = context_ph->thread[id].last_meal.tv_sec * 1000000;
		last_meal += context_ph->thread[id].last_meal.tv_usec;;
		if ((current - last_meal) > (context_ph->time_to_die * 1000))
		{
			pthread_mutex_lock(&context_ph->mutex_red_alert->mutex);
			context_ph->mutex_red_alert->data = 1;
			pthread_mutex_unlock(&context_ph->mutex_red_alert->mutex);
			return ;
		}
		pthread_mutex_lock(&context_ph->mutex_meal_cap->mutex);
		if (context_ph->mutex_meal_cap->data >= context_ph->nb_meals_required)
		{
			printf("Nb_meal_required reached"); ///asd';mapfkonagd
			pthread_mutex_unlock(&context_ph->mutex_meal_cap->mutex);
			return ;
		}
		pthread_mutex_unlock(&context_ph->mutex_meal_cap->mutex);
		id++;
		if (id > context_ph->nb_philo)
			id = 0;
	}*/
	(void)context_ph;
}
