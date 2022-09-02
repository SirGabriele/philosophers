/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:32:13 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/01 21:55:36 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clear_mutex(t_mutex_ph *mutex)
{
	pthread_mutex_destroy(&mutex->mutex_fork);
	pthread_mutex_destroy(&mutex->mutex_write);
}

static void	clear_thread(t_philo_ph *thread)
{
	clear_mutex(thread->mutex);
	if (thread->mutex != NULL)
	{
		free(thread->mutex);
		thread->mutex = NULL;
	}
}

void	clear_program(t_context_ph *context_ph)
{
	int	i;

	i = 1;
	while (i <= context_ph->nb_philo)
	{
		clear_thread(context_ph->thread + i);
		i++;
	}
}
