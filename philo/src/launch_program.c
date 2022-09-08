/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:47:45 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/08 21:02:20 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*monitoring(void *ctx_ph)
{
	t_context_ph	*context_ph;
	int				i;

	i = 0;
	context_ph = (t_context_ph *)ctx_ph;
	pthread_mutex_lock(&context_ph->mutex_start->mutex);
	pthread_mutex_unlock(&context_ph->mutex_start->mutex);
	while (i < context_ph->nb_philo)
	{
		if (pthread_join(context_ph->thread[i].thread, NULL) == -1)
			return (NULL);
		i++;
	}
	return (NULL);
}

static void	*philosopher(void *ctx_ph)
{
	t_context_ph	*context_ph;
	int	id;

	context_ph = (t_context_ph *)ctx_ph;
	pthread_mutex_lock(&context_ph->mutex_i->mutex);
	id = context_ph->mutex_i->data;
	(void)id;
	context_ph->mutex_i->data++;;
	pthread_mutex_unlock(&context_ph->mutex_i->mutex);
	pthread_mutex_lock(&context_ph->mutex_start->mutex);
	pthread_mutex_unlock(&context_ph->mutex_start->mutex);
	routine(context_ph, id);
	return (NULL);
}

static int	create_threads(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	if (pthread_create(&context_ph->monitoring.thread, NULL, &monitoring,
			context_ph) == -1)
		return (-1);
	while (i < context_ph->nb_philo)
	{
		if (pthread_create(&context_ph->thread[i].thread,
			NULL, &philosopher,	context_ph) == -1)
			return (-1);
		i++;
	}
	pthread_mutex_unlock(&context_ph->mutex_start->mutex);
	return (0);
}

int	launch_program(t_context_ph *context_ph)
{
	create_threads(context_ph);
	if (pthread_join(context_ph->monitoring.thread, NULL) == -1)
		return (-1);
	return (0);
}
