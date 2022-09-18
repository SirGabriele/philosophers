/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:31:38 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 01:24:52 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_context_ph	context_ph;

	if (argc < 5 || argc > 6)
	{
		printf("Correct usage is :\n./philo [number_of_philosophers]"\
		" [time_to_die] [time_to_eat] [time_to_sleep]\n"\
		"((( [number_of_times_each_philosopher_must_eat] )))\n");
		return (-1);
	}
	if (check_args(argv) == -1)
		return (-1);
	init_context_ph(&context_ph, argv);
	if (launch_program(&context_ph) == -1)
		return (-1);
	return (0);
}
