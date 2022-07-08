/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:56:01 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/08 01:38:58 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	not_only_digits(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	check_inputs(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo [number of philosophers] [time to eat]");
		printf(" [time to sleep] [time to die] [number of times to eat*]\n");
		return (1);
	}
	while (--argc > 0)
	{
		if (not_only_digits(argv[argc]))
			return (printf("Parameters must be numeric!!\n"), 2);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (check_inputs(argc, argv))
		return (1);
	if (init_program(&table, argc, argv))
		return (2);
	if (feast(&table))
		return (3);
	return (0);
}
