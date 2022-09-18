/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 07:54:31 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/18 07:54:38 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message_think(t_context_ph *context_ph, int id)
{
	long long	current;

	current = get_timestamp();
	pthread_mutex_lock(&context_ph->mutex_write);
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex); //lock repas
	if (context_ph->mutex_death_alert.data == 1)
	{
		pthread_mutex_unlock(&context_ph->mutex_write);
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
		return ;
	}
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
	printf("\e[1;32m%5lld %3d is thinking\e[0m\n", (current - context_ph->time_start_sim) / 1000, id + 1);
	pthread_mutex_unlock(&context_ph->mutex_write);
}

void	print_message_fork(t_context_ph *context_ph, int id)
{
	long long	current;

	current = get_timestamp();
	pthread_mutex_lock(&context_ph->mutex_write);
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex); //lock repas
	if (context_ph->mutex_death_alert.data == 1)
	{
		pthread_mutex_unlock(&context_ph->mutex_write);
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
		return ;
	}
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
	printf("\e[1;36m%5lld %3d has taken a fork\e[0m\n", (current - context_ph->time_start_sim) / 1000, id + 1);
	pthread_mutex_unlock(&context_ph->mutex_write);
}

void	print_message_eat(t_context_ph *context_ph, int id)
{
	long long	current;

	current = get_timestamp();
	pthread_mutex_lock(&context_ph->mutex_write);
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex); //lock repas
	if (context_ph->mutex_death_alert.data == 1)
	{
		pthread_mutex_unlock(&context_ph->mutex_write);
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
		return ;
	}
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
	printf("\e[1;33m%5lld %3d is eating\e[0m\n", (current - context_ph->time_start_sim) / 1000, id + 1);
	pthread_mutex_unlock(&context_ph->mutex_write);
}


void	print_message_sleep(t_context_ph *context_ph, int id)
{
	long long	current;

	current = get_timestamp();
	pthread_mutex_lock(&context_ph->mutex_write);
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex); //lock repas
	if (context_ph->mutex_death_alert.data == 1)
	{
		pthread_mutex_unlock(&context_ph->mutex_write);
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
		return ;
	}
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
	printf("\e[1;34m%5lld %3d is sleeping\e[0m\n", (current - context_ph->time_start_sim) / 1000, id + 1);
	pthread_mutex_unlock(&context_ph->mutex_write);
}
