/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:00:15 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/08 12:57:21 by kbrousse         ###   ########.fr       */
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

typedef struct s_philo_ph	t_philo_ph;
typedef struct s_context_ph	t_context_ph;
typedef struct s_mutex_ph	t_mutex_ph;

struct s_mutex_ph
{
	int					data;
	pthread_mutex_t		mutex;
};

struct s_philo_ph
{
	pthread_t			thread;
	int					philo_id;
	int					red_alert;
	struct timeval	last_meal;
};

struct s_context_ph
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals_required;
	int				*forks_tab;
	t_philo_ph		thread[1024];
	t_philo_ph		monitoring;
	t_mutex_ph		*mutex_i;
	t_mutex_ph		*mutex_fork;
	t_mutex_ph		*mutex_write;
	t_mutex_ph		*mutex_start;
	struct timeval	time_start_sim;
};

int				check_args(char **argv);
int				launch_program(t_context_ph *context_ph);
void			routine(t_context_ph *context_ph, int id);
void			clear_program(t_context_ph *context_ph);

//Init
int				init_context_ph(t_context_ph *context_ph, char **argv);

//Utils
void			*ft_calloc(size_t size, size_t nmemb);
void			*ft_memset(void *s, int c, size_t n);
int				is_an_int(char *tab);
long int		ft_atol(const char *nptr);

#endif
