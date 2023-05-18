/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:00:03 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/18 01:20:33 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_mutex[philo->fork[0]]);
	write_status(philo, 0, FORK_1);
	philo_time_to(philo->table, philo->table->time_to_die);
	write_status(philo, 0, DIED);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->fork[0]]);
	return (NULL);
}
