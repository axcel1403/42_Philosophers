/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:15 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/17 22:01:09 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	threads_routine_reaper(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_create(&table->philos[i]->thread, NULL, &routine,
			table->philos[i]);
		i++;
	}
	if (table->nb_philos > 1)
	{
		pthread_create(&table->reaper, NULL, &reaper, table);
	}
}

int	main(int argc, char **argv)
{
	int		code;
	t_table	*table;

	code = valid_args(argc, argv);
	if (code == 0)
	{
		table = NULL;
		if (!init_all(argc, argv, &table))
		{
			error(-1, table);
			return (EXIT_FAILURE);
		}
		threads_routine_reaper(table);
		clear_all(table);
	}
	else
	{
		error(code, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
