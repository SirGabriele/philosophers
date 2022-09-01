/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:32:13 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/01 21:55:36 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_program(t_context_ph *context_ph)
{
	int	i;

	i = 0;
	while (i < context_ph->nb_philo)
	{
		pthread_mutex_destroy(&context_ph->thread[i].mutex_fork);
		pthread_mutex_destroy(&context_ph->thread[i].mutex_write);
		i++;
	}
}
