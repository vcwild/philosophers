/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:56:01 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/07 19:16:53 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		not_only_digits(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int		check_inputs(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo [number of philosophers] [time to eat] [time to sleep] ");
		printf("[time to die] [number of times to eat (optional)]\n");
		return (1);
	}
	while (--argc > 0)
	{
		if (not_only_digits(argv[argc]))
		{
			printf("Parameters must be numeric!!\n");
			return (1);
		}
	}
	return (0);
}


int		main(int argc, char *argv[])
{
	if (check_inputs(argc, argv))
		return (1);

}
