/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:47:45 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/01 22:40:49 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *philo)
{
	t_philo_ph	*copy;

	copy = (t_philo_ph *)philo;
	printf("begin routine\n");
	pthread_mutex_lock(&copy->mutex_fork);
	if (copy->context_ph->nb_forks_available >= 2)
	{
		copy->context_ph->nb_forks_available -= 2;
		printf("philo %d is eating\n", copy->philo_id);
	}
	pthread_mutex_unlock(&copy->mutex_fork);
	return ((void *)1);
}

int	launch_program(t_context_ph *context_ph)
{
	int	i;
	int	*mem;

	i = 1;
	while (i <= context_ph->nb_philo)
	{
		mem = malloc(sizeof(int *));
		mem = &i;
		if (pthread_create(&context_ph->thread[*mem].thread, NULL, &routine,
				&context_ph->thread[*mem]) == -1)
			return (-1);
		free(mem);
		mem = NULL;
		i++;
	}
	i = 1;
	while (i <= context_ph->nb_philo)
	{
		if (pthread_join(context_ph->thread[i].thread, NULL) == -1)
			return (-1);
		i++;
		printf("end routine\n");
	}
	return (0);
}
