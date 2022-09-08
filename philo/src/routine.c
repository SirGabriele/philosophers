/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:06:16 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/08 21:16:06 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"





/* FAIRE DES LOCK UNLOCK A CHAQUE UTILISATION DE ID*/








static void	check_death(t_context_ph *context_ph, int id)
{
	printf("Start of sim %ld seconds | %ld\n", context_ph->time_start_sim.tv_sec, context_ph->time_start_sim.tv_usec);
	printf("Current time %ld seconds | %ld\n", context_ph->thread[id].last_meal.tv_sec, context_ph->thread[id].last_meal.tv_usec);
	(void)id;
}

static void	eats(t_context_ph *context_ph, int id)
{
	gettimeofday(&context_ph->thread[id].last_meal, NULL);
	usleep(context_ph->time_to_eat * 1000);
}

static void	takes_forks(t_context_ph *context_ph, int id)
{
	pthread_mutex_lock(&context_ph->mutex_fork->mutex);
	if (id == 0)
	{
		if (context_ph->forks_tab[id] == 1
			&& context_ph->forks_tab[context_ph->nb_philo - 1] == 1)
		{
			context_ph->forks_tab[id] = 0;
			context_ph->forks_tab[context_ph->nb_philo - 1] = 0;
		}
	}
	if (context_ph->forks_tab[id] && context_ph->forks_tab[id - 1])
	{
		context_ph->forks_tab[id] = 0;
		context_ph->forks_tab[id - 1] = 0;
	}
	pthread_mutex_unlock(&context_ph->mutex_fork->mutex);
	printf("%d\n", id);
}

void	routine(t_context_ph *context_ph, int id)
{
	int	i;

	i = 0;
	while (/*context_ph->thread[id].red_alert != 1*/ i < 1)
	{
		takes_forks(context_ph, id);
		check_death(context_ph, id);
		eats(context_ph, id);
		check_death(context_ph, id);
/*		sleeps(context_ph, id);*/usleep(context_ph->time_to_sleep * 1000);
		check_death(context_ph, id);
/*		thinks(context_ph, id);*/
		check_death(context_ph, id);
		i++;
	}
	(void)id;
	return ;
}
