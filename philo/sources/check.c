/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:42:26 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/15 13:42:28 by vwildner         ###   ########.fr       */
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

int	check_inputs(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo [number of philosophers] [time to eat]");
		printf(" [time to sleep] [time to die] [number of times to eat*]\n");
		return (1);
	}
	while (--argc > 0)
		if (not_only_digits(argv[argc]))
			return (printf("Parameters must be numeric!!\n"), 2);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > MAX_PHILO
		|| ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (printf("Invalid parameters!!\n"), 2);
	if (argv[5] && ft_atoi(argv[5]) < 0)
		return (printf("Number of meals must be positive!!\n"), 3);
	return (0);
}
