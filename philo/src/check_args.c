/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:34:09 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/01 22:00:39 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_minus_plus_usage(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i] != '\0')
	{
		if (((argv[i] == '+' || argv[i] == '-')
				&& (argv[i + 1] < 48 || argv[i + 1] > 57))
			|| ((argv[i] >= 48 && argv[i] <= 57)
				&& ((argv[i + 1] == '+') || argv[i + 1] == '-')))
			return (-1);
	}
	return (0);
}

static int	count_numbers(char *argv)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (argv[++i] != '\0')
	{
		if (argv[i] >= 48 && argv[i] <= 57)
		{
			count++;
			while (argv[i] != ' ' && argv[i] != '\0')
				i++;
			if (argv[i] == '\0')
				break ;
		}
	}
	return (count);
}

static int	check_charac_validity(char *argv)
{
	char	*tab;
	int		i;
	int		j;

	i = -1;
	tab = "0123456789-+ ";
	while (argv[++i] != '\0')
	{
		j = -1;
		while (++j < 13)
		{
			if (argv[i] == tab[j])
				break ;
			if (j == 12)
				return (-1);
		}
	}
	return (0);
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

int	check_args(t_context_ph *context_ph, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i] != NULL)
	{
		if (check_minus_plus_usage(argv[i]) == -1
			|| check_charac_validity(argv[i]) == -1
			|| count_numbers(argv[i]) > 1
			|| is_an_int(argv[i]) == -1)
		{
			printf("Error\nInvalid argument at parameter #%d\n", i);
			return (-1);
		}
	}
	init_context_ph(context_ph);
	fill_data_struct_context_ph(context_ph, argv);
	if (context_ph->nb_meals_required <= 0 && argv[5] != NULL)
	{
		printf("Number of meal asked is equal or less than 0\n");
		return (-1);
	}
	return (0);
}
