/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:39:52 by jmiranda          #+#    #+#             */
/*   Updated: 2023/07/12 13:41:35 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_table **table)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * (*table)->nb_philos);
	if (!forks)
		return (0);
	i = 0;
	while (i < (*table)->nb_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	(*table)->forks_mutex = forks;
	pthread_mutex_init(&(*table)->stop_mutex, NULL);
	pthread_mutex_init(&(*table)->write_mutex, NULL);
	return (1);
}

t_philo	**init_philos(t_table *table)
{
	int		i;
	t_philo	**philos;

	philos = (t_philo **)malloc(sizeof(t_philo) * table->nb_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < table->nb_philos)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		philos[i]->table = table;
		pthread_mutex_init(&philos[i]->meal_time_mutex, NULL);
		philos[i]->id = i;
		philos[i]->nb_ate = 0;
		philos[i]->fork[0] = philos[i]->id;
		philos[i]->fork[1] = (philos[i]->id + 1) % table->nb_philos;
		if ((philos[i]->id % 2) == 1)
		{
			philos[i]->fork[0] = (philos[i]->id + 1) % table->nb_philos;
			philos[i]->fork[1] = philos[i]->id;
		}
	}
	return (philos);
}

t_table	*init_table(int argc, char **argv)
{
	int		i;
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	i = 1;
	table->nb_philos = (int)atoss(argv[i++]);
	table->time_to_die = (int)atoss(argv[i++]);
	table->time_to_eat = (int)atoss(argv[i++]);
	table->time_to_sleep = (int)atoss(argv[i++]);
	if (argc == 6)
		table->nb_must_eat = (int)atoss(argv[i]);
	else
		table->nb_must_eat = -1;
	return (table);
}

int	init_all(int argc, char **argv, t_table **table)
{
	(*table) = init_table(argc, argv);
	if (!(*table))
		return (0);
	(*table)->philos = init_philos(*table);
	if (!(*table)->philos)
		return (0);
	if (!init_mutexes(table))
		return (0);
	(*table)->stop_flag = 0;
	(*table)->start_time = get_time_in_ms();
	return (1);
}
