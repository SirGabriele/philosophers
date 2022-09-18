/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 01:11:36 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 21:37:13 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_context_ph *context_ph)
{
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex); //lock repas
	if (context_ph->mutex_death_alert.data == 1)
	{
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //lock repas
		return (-1);
	}
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
	return (0);
}

static void	update_last_meal_timer(t_context_ph *context_ph, int id)
{
	pthread_mutex_lock(&context_ph->thread[id].mutex_last_meal);
	gettimeofday(&context_ph->thread[id].last_meal, NULL);
	pthread_mutex_unlock(&context_ph->thread[id].mutex_last_meal);
}

/*static void	manage_meal_counters(t_context_ph *context_ph, int id)
{

}*/

static void	take_forks_and_eat(t_context_ph *context_ph, int id)
{
	pthread_mutex_lock(&context_ph->thread[id].mutex_fork);
	print_message_fork(context_ph, id);
	if (context_ph->nb_philo == 1)
	{
		pthread_mutex_unlock(&context_ph->thread[id].mutex_fork);
		ft_better_usleep(context_ph, context_ph->time_to_eat * 10000);
		return ;
	}
	if (id == context_ph->nb_philo - 1)
		pthread_mutex_lock(&context_ph->thread[0].mutex_fork);
	else
		pthread_mutex_lock(&context_ph->thread[id + 1].mutex_fork);
	print_message_fork(context_ph, id);
	print_message_eat(context_ph, id);
	update_last_meal_timer(context_ph, id);
	ft_better_usleep(context_ph, context_ph->time_to_eat * 1000);//add meal_counter
	pthread_mutex_unlock(&context_ph->thread[id].mutex_fork);
	if (id == context_ph->nb_philo - 1)
		pthread_mutex_unlock(&context_ph->thread[0].mutex_fork);
	else
		pthread_mutex_unlock(&context_ph->thread[id + 1].mutex_fork);
}

void	routine(t_context_ph *context_ph, int id)
{
	update_last_meal_timer(context_ph, id);
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);//lock repas
	while (context_ph->mutex_death_alert.data != 1)
	{
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);//unlock repas
		print_message_think(context_ph, id);
		if (check_death(context_ph) == -1)
		{
			pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);//lock repas
			break ;
		}
		take_forks_and_eat(context_ph, id);
		if (check_death(context_ph) == -1)
		{
			pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);//lock repas
			break ;
		}
		print_message_sleep(context_ph, id);
		ft_better_usleep(context_ph, context_ph->time_to_sleep * 1000);
		pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);//lock repas
	}
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);//unlock repas
}
