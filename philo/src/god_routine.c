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
	long double		start;
	long double		last_meal;

	start = context_ph->time_start_sim.tv_sec * 1000000;
	start += context_ph->time_start_sim.tv_usec;
	id = 0;
	while (context_ph->red_alert != 1)
	{
		last_meal = context_ph->thread[id].last_meal.tv_sec * 1000000;
		last_meal += context_ph->thread[id].last_meal.tv_usec;
		if (last_meal - start > context_ph->time_to_die * 1000)
		{
			context_ph->red_alert = 1;
			return ;
		}
		id++;
		if (id > context_ph->nb_philo)
			id = 0;
	}*/
	(void)context_ph;
}
