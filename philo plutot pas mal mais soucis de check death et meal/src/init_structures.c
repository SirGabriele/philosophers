/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:32:54 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 01:27:40 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex_structure(t_mutex_ph *mutex)
{
	mutex->data = 0;
	pthread_mutex_init(&mutex->mutex, NULL);
}

void	init_mutex_in_each_thread(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	while (i < context_ph->nb_philo)
	{
		pthread_mutex_init(&context_ph->thread[i].mutex_fork, NULL);
		pthread_mutex_init(&context_ph->thread[i].mutex_last_meal, NULL);
		context_ph->thread[i].meal_counter = 0;
		i++;
	}
}

void	fill_data_struct_context_ph(t_context_ph *context_ph, char **argv)
{
	context_ph->nb_philo = ft_atoi(argv[1]);
	context_ph->time_to_die = ft_atoi(argv[2]);
	context_ph->time_to_eat = ft_atoi(argv[3]);
	context_ph->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		context_ph->meal_limit = ft_atoi(argv[5]);
	else
		context_ph->meal_limit = -1;
}

void	init_context_ph(t_context_ph *context_ph, char **argv)
{
	fill_data_struct_context_ph(context_ph, argv);
	init_mutex_in_each_thread(context_ph);
	init_mutex_structure(&context_ph->mutex_i);
	init_mutex_structure(&context_ph->mutex_death_alert);
	init_mutex_structure(&context_ph->mutex_meal_alert);
	init_mutex_structure(&context_ph->mutex_meal_finished);
	pthread_mutex_init(&context_ph->mutex_write, NULL);
}
