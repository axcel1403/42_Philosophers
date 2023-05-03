/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:15 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/03 00:49:51 by jmiranda         ###   ########.fr       */
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
						return (0);
					i++;
				}
				return (1);
			}
			return (0);
		}
		return (0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
/*	int code;

	code = valid_args(argc, argv);
	if (code == 1)
	{

	}
	else
		error(code);*/
	printf("Number of arguments: %d\n", argc);
	printf("argv[1]: %s\n", argv[1]);
	if (valid_args(argc, argv))
	{

	}
	else
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
