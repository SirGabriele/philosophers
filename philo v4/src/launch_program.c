/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:43:24 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 01:24:17 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*monitoring(void *ctx_ph)
{
	t_context_ph	*context_ph;

	context_ph = (t_context_ph *)ctx_ph;
	god_routine(context_ph);
	return (NULL);
}

static void	*philosopher(void *ctx_ph)
{
	t_context_ph	*context_ph;
	int				id;

	context_ph = (t_context_ph *)ctx_ph;
	pthread_mutex_lock(&context_ph->mutex_i.mutex);
	id = context_ph->mutex_i.data;
	context_ph->mutex_i.data++;
	pthread_mutex_unlock(&context_ph->mutex_i.mutex);
	if (id % 2 == 1)
		usleep(100);
	routine(context_ph, id);
	return (NULL);
}

int	launch_program(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	gettimeofday(&context_ph->time_start_sim, NULL);
	while (i < context_ph->nb_philo)
	{
		if (pthread_create(&context_ph->thread[i].thread,
				NULL, &philosopher, context_ph) == -1)
			return (-1);
		i++;
	}
	usleep(100);
	if (pthread_create(&context_ph->monitoring, NULL,
			&monitoring, context_ph) == -1)
		return (-1);
	if (pthread_join(context_ph->monitoring, NULL) == -1)
		return (-1);
	i = 0;
	while (i < context_ph->nb_philo)
	{
		if (pthread_join(context_ph->thread[i].thread, NULL) == -1)
			return (-1);
		i++;
	}
	return (0);
}
