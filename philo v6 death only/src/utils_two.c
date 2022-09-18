/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:39:45 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 19:00:35 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_timestamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000000 + current_time.tv_usec);
}

void	ft_better_usleep(t_context_ph *context_ph, int usec)
{
	long long	start;

	start = get_timestamp();
	while (get_timestamp() - start < usec)
	{
		pthread_mutex_lock(&context_ph->mutex_death_alert.mutex); //lock repas
		if (context_ph->mutex_death_alert.data == 1)
		{
			pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
			return ;
		}
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
		usleep(50);
	}
}
