/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:49:48 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 16:15:03 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//peut déplacer le mutex du die dans le if de la fonction check_death
static void	print_message_death(t_context_ph *context_ph, int id)
{
	long long	current;

	current = get_timestamp();
	pthread_mutex_lock(&context_ph->mutex_write);
	printf("\e[41m%5lld %3d died\e[0m\n", (current - context_ph->time_start_sim) / 1000, id + 1);
	pthread_mutex_unlock(&context_ph->mutex_write);
}

/*static void	check_meal_limit(t_context_ph *context_ph)
{

}*/

static int	check_death(t_context_ph *context_ph, int id)
{
	long long	lm;
	long long	ts;

	pthread_mutex_lock(&context_ph->thread[id].mutex_last_meal);
	lm = context_ph->thread[id].last_meal.tv_sec * 1000000;
	lm += context_ph->thread[id].last_meal.tv_usec;
	pthread_mutex_unlock(&context_ph->thread[id].mutex_last_meal);
	ts = get_timestamp();
	if (((ts - lm) / 1000) > context_ph->time_to_die)
	{
		pthread_mutex_lock(&context_ph->mutex_death_alert.mutex);
		context_ph->mutex_death_alert.data = 1;
		print_message_death(context_ph, id);
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex);
		return (-1);
	}
	return (0);
}

void	god_routine(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&context_ph->mutex_death_alert.mutex); //lock repas
	while (context_ph->mutex_death_alert.data != 1) // add repas
	{
		pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //lock repas
		if (check_death(context_ph, i) == -1) // add check_meal
		{
			pthread_mutex_lock(&context_ph->mutex_death_alert.mutex); //lock repas
			break ;
		}
		i++;
		if (i == context_ph->nb_philo)
			i = 0;
		pthread_mutex_lock(&context_ph->mutex_death_alert.mutex); //lock repas
	}
	pthread_mutex_unlock(&context_ph->mutex_death_alert.mutex); //unlock repas
}
