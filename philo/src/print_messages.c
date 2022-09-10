/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:02:41 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/10 20:26:17 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_context_ph *context_ph, int id, char *msg)
{
	struct timeval	current_time;
	long long		current;
	long long		start;

	gettimeofday(&current_time, NULL);
	current = current_time.tv_sec * 1000000 + current_time.tv_usec;
	start = context_ph->time_start_sim.tv_sec * 1000000;
	start += context_ph->time_start_sim.tv_usec;
	printf("%.0lld %d %s\n", (current - start) / 1000, id + 1, msg);	
}
