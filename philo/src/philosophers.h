/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:05:47 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/05 23:54:42 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

# define PHILOS_MAX 200;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				fork[2];
	int				nb_eat;
	pthread_mutex_t	meal_time_mutex;
	time_t			last_meal;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				nb_philos;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	int				philo_stop;
	pthread_mutex_t	philo_stop_mutex;
	pthread_mutex_t	philo_write_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_t		reaper;
	t_philo			**philos;
}	t_table;

typedef enum e_status
{
	DIED = 0;
	EATING = 1;
	SLEEPING = 2;
	THINKING = 3;
	FORK_1 = 4;
	FORK_2 = 5;
}	t_status;

#endif
