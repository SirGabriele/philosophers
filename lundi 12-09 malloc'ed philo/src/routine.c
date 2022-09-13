/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:15:21 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/12 16:32:40 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//tous les checks de morts sont fait par dieu. Les philos ne checkent que les deux booleens pour meal_cap et red_alert

int	routine(t_context_ph *context_ph, int id)
{
/*	gettimeofday(&context_ph->thread[id].last_meal, NULL);
	pthread_mutex_lock(&context_ph->mutex_red_alert->mutex);
	pthread_mutex_lock(&context_ph->mutex_meal_cap->mutex);
	while (context_ph->mutex_red_alert != 1
			&& context_ph->mutex_meal_cap->data < context_ph->nb_meals_required)
	{
		pthread_mutex_unlock(&context_ph->mutex_red_alert->mutex);
		pthread_mutex_unlock(&context_ph->mutex_meal_cap->mutex);
			sdaofpkadmf
		


		pthread_mutex_lock(&context_ph->mutex_red_alert->mutex);
		pthread_mutex_lock(&context_ph->mutex_meal_cap->mutex);
	}*/
	(void)context_ph;
	(void)id;
	return (0);
}
