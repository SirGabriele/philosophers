/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:32:13 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/08 15:00:35 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clear_mutex(t_mutex_ph *mutex)
{
	pthread_mutex_destroy(&mutex->mutex);
	free(mutex);
	mutex = NULL;
}

void	clear_program(t_context_ph *context_ph)
{
	if (context_ph->forks_tab != NULL)
		free(context_ph->forks_tab);
	if (context_ph->mutex_i != NULL)
		clear_mutex(context_ph->mutex_i);
	if (context_ph->mutex_fork != NULL)
		clear_mutex(context_ph->mutex_fork);
	if (context_ph->mutex_write != NULL)
		clear_mutex(context_ph->mutex_write);
	if (context_ph->mutex_red_alert != NULL)
		clear_mutex(context_ph->mutex_red_alert);
}
