/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:40:58 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/17 21:41:48 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	if (table->forks_mutex != NULL)
		free(table->forks_mutex);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return ;
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->forks_mutex[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
}

void	clear_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->nb_philos > 1)
		pthread_join(table->reaper, NULL);
	destroy_mutexes(table);
	clear_table(table);
}

void	error(int code, t_table *table)
{
	(void) table;
	write(2, "Error\n", 6);
	if (code == 1)
		printf("Wrong Number Of Arguments\n");
	if (code == 2)
		printf("Some Arguments Are Not Digits\n");
	if (code == 3)
		printf("Number Of Philosophers Must Be Between 1 And 200\n");
	if (code == 4)
		printf("Number Is Greater Than INT_MAX\n");
	if (code == -1)
	{
		destroy_mutexes(table);
		clear_table(table);
	}
}
