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

static void	print_message_god(t_context_ph *context_ph, int id, char *msg)
{
	long long	current;
	long long	start;

	current = get_timestamp();
	start = context_ph->time_start_sim.tv_sec * 1000000;
	start += context_ph->time_start_sim.tv_usec;
	pthread_mutex_lock(&context_ph->mutex_write);
	printf("%lld %d %s\n", (current - start) / 1000, id + 1, msg);
	pthread_mutex_unlock(&context_ph->mutex_write);
}

static void	check_meal_limit(t_context_ph *context_ph)
{
	if (context_ph->mutex_meal_finished.data >= context_ph->meal_limit)
	{
		printf("All philosophers ate the required amount of times\n");//sdadasdasd
		context_ph->mutex_meal_alert.data = 1;
	}
}


//GROS SOUCIS ICI
static void	check_death(t_context_ph *context_ph, int id)
{
	long long	lm;
	long long	ts;
	
	pthread_mutex_lock(&context_ph->thread[id].mutex_last_meal);
	lm = context_ph->thread[id].last_meal.tv_sec * 1000000;
	lm += context_ph->thread[id].last_meal.tv_usec;
	printf("lm avant boucle = %lld\n", lm);
	pthread_mutex_unlock(&context_ph->thread[id].mutex_last_meal);
	ts = get_timestamp();
	if ((ts - lm) > (context_ph->time_to_die * 1000))
	{
		pthread_mutex_lock(&context_ph->mutex_write);
		printf("ts = %lld\n", ts);
		printf("lm = %lld\n", lm);
		printf("ts - lm = %lld\n", (ts - lm) / 1000);
		pthread_mutex_lock(&context_ph->mutex_write);
		context_ph->mutex_death_alert.data = 1;
		print_message_god(context_ph, id, "died");
	}
}

void	god_routine(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	lock_death_and_meal_mutex(context_ph);
	while (context_ph->mutex_death_alert.data != 1
		&& context_ph->mutex_meal_alert.data != 1)
	{
		unlock_death_and_meal_mutex(context_ph);
		lock_death_and_meal_mutex(context_ph);
		check_death(context_ph, i);
		if (context_ph->meal_limit > 0)
			check_meal_limit(context_ph);
		i++;
		if (i == context_ph->nb_philo)
			i = 0;
		unlock_death_and_meal_mutex(context_ph);
		lock_death_and_meal_mutex(context_ph);
	}
	unlock_death_and_meal_mutex(context_ph);
}
