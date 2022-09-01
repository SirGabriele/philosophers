/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:00:15 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/01 21:59:10 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo_ph t_philo_ph;
typedef struct s_context_ph t_context_ph;

struct s_philo_ph
{
	pthread_t			thread;
	int					philo_id;
	pthread_mutex_t		mutex_fork;
	pthread_mutex_t		mutex_write;
	t_context_ph			*context_ph;
};

struct s_context_ph
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals_required;
	t_philo_ph		thread[200];
	int				nb_forks_available;
	struct timeval	time_start_sim;
};

int				check_args(t_context_ph *context_ph, char **argv);
int				launch_program(t_context_ph *context_ph);
void			clear_program(t_context_ph *context_ph);

//Init
void			init_context_ph(t_context_ph *context_ph);

//Utils
void			*ft_memset(void *s, int c, size_t n);
int				is_an_int(char *tab);
long int		ft_atol(const char *nptr);

#endif