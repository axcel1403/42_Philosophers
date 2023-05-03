/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:15 by jmiranda          #+#    #+#             */
/*   Updated: 2023/05/02 23:52:19 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_digit(char **argv)
{
	int i;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) || (argv[i][j] == ' '))
					j++;
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	valid_args(int argc, char **argv)
{
	(void) argv;
	if ((argc == 4 + 1) || (argc == 5 + 1))
	{
		if (is_digit(argv))
		{
			
		}
		return (0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
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
