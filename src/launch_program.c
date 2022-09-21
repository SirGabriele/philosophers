/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:43:24 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/21 17:55:54 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_time_start_sim(t_context_ph *context_ph)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	context_ph->time_start_sim = start.tv_sec * 1000000;
	context_ph->time_start_sim += start.tv_usec;
}

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
	routine(context_ph, id);
	return (NULL);
}

int	launch_program(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	set_time_start_sim(context_ph);
	while (i < context_ph->nb_philo)
	{
		if (pthread_create(&context_ph->thread[i].thread,
				NULL, &philosopher, context_ph) == -1)
			return (-1);
		usleep(50);
		i++;
	}
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
