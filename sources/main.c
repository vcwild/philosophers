/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:56:01 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/09 03:15:46 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	not_only_digits(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

static int	check_inputs(int argc, char *argv[])
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

static int	leave_table(t_table *t)
{
	int	status;
	int	i;

	i = -1;
	while (++i < t->n_philos)
	{
		status = pthread_mutex_destroy(&t->fork[i]);
		if (status)
			return (status);
	}
	status = pthread_mutex_destroy(&t->feeder);
	return (status);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (check_inputs(argc, argv))
		return (1);
	if (receive_guests(&table, argc, argv))
		return (2);
	if (feast(&table))
		return (3);
	if (leave_table(&table))
		return (4);
	return (0);
}
