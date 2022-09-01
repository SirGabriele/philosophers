/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context_ph.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:28:56 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/01 22:46:20 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	init_context_ph(t_context_ph *context_ph)
{
	int	i;

	i = 1;
	gettimeofday(&context_ph->time_start_sim, NULL);
	while (i <= context_ph->nb_philo)
	{
		context_ph->thread[i].philo_id = i;
		pthread_mutex_init(&context_ph->thread[i].mutex_fork, NULL);
		pthread_mutex_init(&context_ph->thread[i].mutex_write, NULL);
		context_ph->thread[i].context_ph = context_ph;
		i++;
	}
}
