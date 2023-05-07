/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:15 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/06 21:37:15 by jmiranda         ###   ########.fr       */
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
	int	code;

	code = valid_args(argc, argv);
	if (code == 0)
	{
		printf("Number of arguments: %d\n", argc);
		printf("argv[1]: %s\n", argv[1]);
	}
	else
	{
		error(code);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
