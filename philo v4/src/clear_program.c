/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:13:27 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 01:28:21 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clear_mutex_in_each_thread(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	while (i < context_ph->nb_philo)
	{
		pthread_mutex_destroy(&context_ph->thread[i].mutex_write);
		pthread_mutex_destroy(&context_ph->thread[i].mutex_last_meal);
		i++;
	}
}

void	clear_program(t_context_ph *context_ph)
{
	clear_mutex_each_thread(context_ph);
	pthread_mutex_destroy(&context_ph->mutex_i.mutex);
	pthread_mutex_destroy(&context_ph->mutex_death_alert.mutex);
	pthread_mutex_destroy(&context_ph->mutex_meal_alert.mutex);
	pthread_mutex_destroy(&context_ph->mutex_meal_finished.mutex);
	pthread_mutex_destroy(&context_ph->mutex_write);
}
