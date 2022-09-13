/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:28:56 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/10 20:27:15 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	init_mutex_generic(t_mutex_ph **mutex)
{
	*mutex = NULL;
	*mutex = ft_calloc(sizeof(t_mutex_ph), 1);
	if (*mutex == NULL)
		return (-1);
	(*mutex)->data = 0;
	pthread_mutex_init(&(*mutex)->mutex, NULL);
	return (0);
}

static int	init_mutex_forks(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	context_ph->mutex_fork = ft_calloc(sizeof(t_mutex_ph),
			context_ph->nb_philo);
	if (context_ph->mutex_fork == NULL)
		return (-1);
	while (i < context_ph->nb_philo)
	{
		context_ph->mutex_fork[i].data = 0;
		pthread_mutex_init(&context_ph->mutex_fork[i].mutex, NULL);
		i++;
	}
	return (0);
}

static int	init_mutex_context_ph(t_context_ph *context_ph)
{
	if (init_mutex_generic(&context_ph->mutex_i) == -1
		|| init_mutex_forks(context_ph) == -1
		|| init_mutex_generic(&context_ph->mutex_write) == -1
		|| init_mutex_generic(&context_ph->mutex_death_alert) == -1
		|| init_mutex_generic(&context_ph->mutex_meal_alert) == -1
		|| init_mutex_generic(&context_ph->mutex_meal_finished) == -1)
		return (-1);
	return (0);
}

static int	fill_data_struct_context_ph(t_context_ph *context_ph, char **argv)
{
	int	i;

	i = 0;
	context_ph->nb_philo = ft_atol(argv[1]);
	context_ph->time_to_die = ft_atol(argv[2]);
	context_ph->time_to_eat = ft_atol(argv[3]);
	context_ph->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		context_ph->nb_meals_required = ft_atol(argv[5]);
	else
		context_ph->nb_meals_required = -1;
	context_ph->forks_tab = ft_calloc(sizeof(int), context_ph->nb_philo);
	if (context_ph->forks_tab == NULL)
		return (-1);
	while (i < context_ph->nb_philo)
	{
		context_ph->forks_tab[i] = 1;
		i++;
	}
	if (init_mutex_context_ph(context_ph) == -1)
		return (-1);
	return (0);
}

int	init_context_ph(t_context_ph *context_ph, char **argv)
{
	if (fill_data_struct_context_ph(context_ph, argv) == -1)
		return (-1);
	return (0);
}