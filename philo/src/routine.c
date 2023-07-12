/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:45:33 by jmiranda          #+#    #+#             */
/*   Updated: 2023/07/12 13:41:42 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_stop(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	if (table->stop_flag)
	{
		pthread_mutex_unlock(&table->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->stop_mutex);
	return (0);
}

void	philo_time_to(t_table *table, time_t action_time)
{
	time_t	action_finished;

	action_finished = get_time_in_ms() + action_time;
	while (get_time_in_ms() < action_finished)
	{
		if (philo_stop(table))
			return ;
		usleep(100);
	}
}

void	eating_sleeping_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_mutex[philo->fork[0]]);
	write_status(philo, 0, FORK_1);
	pthread_mutex_lock(&philo->table->forks_mutex[philo->fork[1]]);
	write_status(philo, 0, FORK_2);
	write_status(philo, 0, EATING);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	philo_time_to(philo->table, philo->table->time_to_eat);
	if (philo_stop(philo->table) == 0)
	{
		pthread_mutex_lock(&philo->meal_time_mutex);
		philo->nb_ate++;
		pthread_mutex_unlock(&philo->meal_time_mutex);
	}
	write_status(philo, 0, SLEEPING);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->fork[0]]);
	philo_time_to(philo->table, philo->table->time_to_sleep);
}

void	thinking_routine(t_philo *philo, int silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_mutex);
	time_to_think = (philo->table->time_to_die
			- (get_time_in_ms() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == 0)
		write_status(philo, 0, THINKING);
	philo_time_to(philo->table, time_to_think);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->time_to_die == 0 || philo->table->nb_must_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	sync_threads_start_time(philo->table->start_time);
	if (philo->table->nb_philos == 1)
		return (one_philo(philo));
	else if (philo->id % 2)
		thinking_routine(philo, 1);
	while (philo_stop(philo->table) == 0)
	{
		eating_sleeping_routine(philo);
		thinking_routine(philo, 0);
	}
	return (NULL);
}
