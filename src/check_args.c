/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:35:13 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/21 17:55:42 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	count_numbers(char *argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] >= 48 && argv[i] <= 57)
		{
			count++;
			while (argv[i] != ' ' && argv[i] != '\0')
				i++;
			if (argv[i] == '\0')
				break ;
		}
		i++;
	}
	return (count);
}

static int	check_charac_validity(char *argv)
{
	char	*tab;
	int		i;
	int		j;

	i = 0;
	tab = "0123456789+ ";
	while (argv[i] != '\0')
	{
		j = 0;
		while (j < 12)
		{
			if (argv[i] == tab[j])
				break ;
			if (j == 11)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_plus_usage(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		if ((argv[i] == '+' && (argv[i + 1] < 48 || argv[i + 1] > 57))
			|| ((argv[i] >= 48 && argv[i] <= 57) && (argv[i + 1] == '+')))
			return (-1);
		i++;
	}
	return (0);
}

int	check_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (check_charac_validity(argv[i]) == -1
			|| check_plus_usage(argv[i]) == -1
			|| count_numbers(argv[i]) == -1
			|| ft_strlen_ignore_left_zeros(argv[i]) > 11
			|| is_an_int(argv[i]) == -1)
		{
			printf("Error\nInvalid argument at parameter #%d\n", i);
			return (-1);
		}
		if ((i == 1 && ft_atoi(argv[i]) > 1024)
			|| (i == 1 && ft_atoi(argv[i]) == 0))
		{
			printf("Error\nInvalid argument at parameter #%d\n", i);
			return (-1);
		}
		i++;
	}
	return (0);
}
