/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:15 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/12 23:52:27 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(int code)
{
	write(2, "Error\n", 6);
	if (code == 1)
		printf("Wrong Number Of Arguments\n");
	if (code == 2)
		printf("Some Arguments Are Not Digits\n");
	if (code == 3)
		printf("Number Of Philosophers Must Be Between 1 And 200\n");
	if (code == 4)
		printf("Number Is Greater Than INT_MAX\n");
//	if (code == -1)
//	{
//		clear_table();
//		destroy_mutexes();
//	}
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeoftheday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *state)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, state);
}

void	write_status(t_philo *philo, int reaper_report, t_status status)
{
	pthread_mutex_lock(&philo->table->write_mutex);
/* TO DO if (philo_stop(philo->table) && reaper_report == 0)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}*/
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == FORK_1 || status == FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	sync_threads_start_time(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_mutex[philo->fork[0]]);
	write_status(philo, 0, FORK_1);
//	TO DO philo_sleeping(philo->table, philo->table->time_to_die);
	write_status(philo, 0, DIED);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->forks[0]]);
	return (NULL);
}

void	*routine(t_philo *philo)
{
	if (philo->table->time_to_die == 0 || philo->table->nb_must_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	sync_threads_start_time(philo->table->start_time);
	if (philo->table->nb_philos == 1)
		return (one_philo(philo));
}

void	create_philos_threads_and_routine(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_create(&table->philos[i]->thread, NULL, &routine,
			table->philos[i]);
		i++;
	}
}

ssize_t	atoss(const char *str)
{
	int		i;
	ssize_t	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res);
}

int	init_mutexes(t_table *table)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!forks)
		return (0);
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	table->forks_mutex = forks;
	pthread_mutex_init(&table->stop_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
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

int	init_all(int argc, char **argv, t_table *table)
{
	table = init_table(argc, argv);
	if (!table)
		return (0);
	table->philos = init_philos(table);
	if (!table->philos)
		return (0);
	if (!init_mutexes(table))
		return (0);
	table->stop_flag = 0;
	table->start_time = get_time_in_ms();
	return (1);
}

int	is_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
					j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	valid_args(int argc, char **argv)
{
	int	i;

	if ((argc == 4 + 1) || (argc == 5 + 1))
	{
		if (is_digit(argv))
		{
			if (atoss(argv[1]) > 0 && atoss(argv[1]) <= 200)
			{
				i = 1;
				while (argv[i] != NULL)
				{
					if (atoss(argv[i]) > INT_MAX)
						return (4);
					i++;
				}
				return (0);
			}
			return (3);
		}
		return (2);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		code;
	t_table	*table;

	code = valid_args(argc, argv);
	if (code == 0)
	{
		printf("Number of arguments: %d\n", argc);
		table = NULL;
		if (!init_all(argc, argv, table))
		{
			error(-1);
			return (EXIT_FAILURE);
		}
		create_philos_threads_and_routine(table);
	}
	else
	{
		error(code);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
