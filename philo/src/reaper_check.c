/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:56:59 by jmiranda          #+#    #+#             */
/*   Updated: 2023/07/12 13:41:41 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	stop_flag(t_table *table, int state)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->stop_flag = state;
	pthread_mutex_unlock(&table->stop_mutex);
}

int	philo_died(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		stop_flag(philo->table, 1);
		write_status(philo, 1, DIED);
		pthread_mutex_unlock(&philo->meal_time_mutex);
		return (1);
	}
	return (0);
}

int	check_stop_all(t_table *table)
{
	int	i;
	int	all_ate_enough;

	all_ate_enough = 1;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_mutex);
		if (philo_died(table->philos[i]))
			return (1);
		if (table->nb_must_eat != -1 && table->philos[i]->nb_ate
			< table->nb_must_eat)
			all_ate_enough = 0;
		pthread_mutex_unlock(&table->philos[i]->meal_time_mutex);
		i++;
	}
	if (table->nb_must_eat != -1 && all_ate_enough == 1)
	{
		stop_flag(table, 1);
		return (1);
	}
	return (0);
}

void	*reaper(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	if (table->nb_must_eat == 0)
		return (NULL);
	stop_flag(table, 0);
	sync_threads_start_time(table->start_time);
	while (1)
	{
		if (check_stop_all(table) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
