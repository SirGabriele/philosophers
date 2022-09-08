/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   it_s_alive.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:06:16 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/08 20:52:40 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_death(context_ph *context_ph, int id)
{
	printf("Start of sim %d seconds | %d", context_ph->time_start_sim.tv_sec, context_ph->time_start_sim.tv_usec);
}

static void	eats(context_ph *context_ph, int id)
{
	gettimeofday(&context_ph->thead[id].last_meal, NULL);
	usleep(context_ph->time_to_eat * 1000);
}

static void	takes_forks(context_ph *context_ph, int id)
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
}

void	routine(t_context_ph *context_ph, int id)
{
	while (context_ph->thread[id].red_alert != 1)
	{
		takes_forks(context_ph, id);
		check_death(context_ph, id);
		eats(contex_ph, id);
		check_death(context_ph, id);
/*		sleeps(context_ph, id);*/usleep(context_ph->time_to_sleep * 1000);
		check_death(context_ph, id);
/*		thinks(context_ph, id);*/
		check_death(context_ph, id);
	}
	return ;
}
