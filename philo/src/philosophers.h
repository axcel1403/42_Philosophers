/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:05:47 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/12 23:24:34 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

# define PHILOS_MAX 200;

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_mutex_t	meal_time_mutex;
	int				id;
	int				nb_ate;
	int				fork[2];
	pthread_t		thread;
	time_t			last_meal;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				nb_must_eat;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	write_mutex;
	int				stop_flag;
	time_t			start_time;
	
	pthread_t		reaper;
	t_philo			**philos;
}	t_table;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	FORK_1 = 4,
	FORK_2 = 5,
}	t_status;

#endif
