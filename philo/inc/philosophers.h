/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:05:47 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/18 01:20:58 by jmiranda         ###   ########.fr       */
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

//		Main
void		threads_routine_reaper(t_table *table);
int			valid_args(int argc, char **argv);
int			is_digit(char **argv);
ssize_t		atoss(const char *str);

//		Initialization
int			init_all(int argc, char **argv, t_table **table);
t_table		*init_table(int argc, char **argv);
t_philo		**init_philos(t_table *table);
int			init_mutexes(t_table **table);

//		Routine
void		*routine(void *arg);
void		thinking_routine(t_philo *philo, int silent);
void		eating_sleeping_routine(t_philo *philo);
void		philo_time_to(t_table *table, time_t action_time);
int			philo_stop(t_table *table);

//		One_philo
void		*one_philo(t_philo *philo);

//		Reaper_check
void		*reaper(void *arg);
int			check_stop_all(t_table *table);
int			philo_died(t_philo *philo);
void		stop_flag(t_table *table, int state);

//		Time_and_print
time_t		get_time_in_ms(void);
void		sync_threads_start_time(time_t start_time);
void		write_status(t_philo *philo, int reaper_report, t_status status);
void		print_status(t_philo *philo, char *state);

//		Error_and_clear
void		error(int code, t_table *table);
void		clear_all(t_table *table);
void		destroy_mutexes(t_table *table);
void		clear_table(t_table *table);

#endif
