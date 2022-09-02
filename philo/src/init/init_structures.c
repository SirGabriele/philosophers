/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:28:56 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/01 22:46:20 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	init_mutex(t_mutex_ph *mutex)
{
	pthread_mutex_init(&mutex->mutex_fork, NULL);
	pthread_mutex_init(&mutex->mutex_write, NULL);
}

static void	init_thread(t_philo_ph *thread, int i, t_context_ph **context_ph)
{
	thread->philo_id = i;
	thread->context_ph = *context_ph;
	thread->mutex = malloc(sizeof(t_mutex_ph));
	if (thread->mutex == NULL)
		clear_program(*context_ph);
	init_mutex(thread->mutex);
}

static void	fill_data_struct_context_ph(t_context_ph *context_ph, char **argv)
{
	context_ph->nb_philo = ft_atol(argv[1]);
	context_ph->time_to_die = ft_atol(argv[2]);
	context_ph->time_to_eat = ft_atol(argv[3]);
	context_ph->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		context_ph->nb_meals_required = ft_atol(argv[5]);
	else
		context_ph->nb_meals_required = -1;
	context_ph->nb_forks_available = context_ph->nb_philo;
}

void	init_context_ph(t_context_ph *context_ph, char **argv)
{
	int	i;

	i = 1;
	gettimeofday(&context_ph->time_start_sim, NULL);
	fill_data_struct_context_ph(context_ph, argv);
	while (i <= context_ph->nb_philo)
	{
		init_thread(context_ph->thread + i, i, &context_ph);
		i++;
	}
}
