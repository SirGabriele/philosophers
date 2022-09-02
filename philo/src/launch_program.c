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
	(void)philo;
	return (NULL);
}

int	launch_program(t_context_ph *context_ph)
{
	int	i;

	i = 1;
	while (i <= context_ph->nb_philo)
	{
		printf("creating thread %d\n", i);
		if (pthread_create(&context_ph->thread[i].thread, NULL, &routine,
				&context_ph->thread[i]) == -1)
			return (-1);
		i++;
	}
	i = 1;
	while (i <= context_ph->nb_philo)
	{
		if (pthread_join(context_ph->thread[i].thread, NULL) == -1)
			return (-1);
		printf("thread %d joined with success\n", i);
		i++;
	}
	return (0);
}
