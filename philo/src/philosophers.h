/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:37:44 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/13 01:27:28 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
///////////////////////////
//	printf;
///////////////////////////

# include <stdlib.h>
///////////////////////////
//	malloc
///////////////////////////

# include <pthread.h>
///////////////////////////
//	pthread_mutex_init
//	pthread_mutex_destroy
//	pthread_create
//	pthread_join
///////////////////////////

# include <sys/time.h>
///////////////////////////
//	gettimeofday
///////////////////////////

# include <unistd.h>
///////////////////////////
//	usleep
///////////////////////////

typedef struct s_context_ph	t_context_ph;
typedef struct s_philo_ph	t_philo_ph;
typedef struct s_mutex_ph	t_mutex_ph;

struct s_mutex_ph
{
	int					data;
	pthread_mutex_t		mutex;
};

struct s_philo_ph
{
	pthread_t		thread;
	struct timeval	last_meal;
	pthread_mutex_t	mutex_fork;
};

struct s_context_ph
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_limit;
	t_philo_ph		thread[1024];
	pthread_t		monitoring;
	t_mutex_ph		mutex_i;
	t_mutex_ph		mutex_death_alert;
	t_mutex_ph		mutex_meal_alert;
	t_mutex_ph		mutex_meal_finished;
	pthread_mutex_t	mutex_write;
	struct timeval	time_start_sim;
};

int			check_args(char **argv);
void		init_context_ph(t_context_ph *context_ph, char **argv);
int			launch_program(t_context_ph *context_ph);
void		routine(t_context_ph *context_ph, int id);

// utils functions
int			ft_strlen_ignore_left_zeros(char *str);	
int			is_an_int(char *tab);
void		*ft_calloc(size_t size, size_t nmemb);
int			ft_atoi(const char *nptr);

#endif
