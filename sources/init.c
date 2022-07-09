/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:57:41 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/09 01:50:48 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_table(t_table *t, int argc, char *argv[])
{
	t->n_philos = ft_atoi(argv[1]);
	t->time_to_die = ft_atoi(argv[2]);
	t->time_to_eat = ft_atoi(argv[3]);
	t->time_to_sleep = ft_atoi(argv[4]);
	t->is_all_alive = 1;
	t->is_all_fed = 0;
	if (argc == 6)
	{
		t->n_meals = ft_atoi(argv[5]);
		if (t->n_meals < 0)
			return (printf("Number of meals must be positive!!\n"), 1);
	}
	else
		t->n_meals = -1;
	return (0);
}

static int	init_philos(t_table *t)
{
	int	i;

	i = t->n_philos;
	if (!t)
		return (1);
	while (--i >= 0)
	{
		t->philo[i].id = i;
		t->philo[i].count_meals = 0;
		t->philo[i].id_left_fork = i;
		t->philo[i].id_right_fork = (i + 1) % t->n_philos;
		t->philo[i].ts_last_meal = 0;
		t->philo[i].id_thread = 0;
		t->philo[i].table = t;
	}
	return (0);
}

static int	init_mutex(t_table *t)
{
	int	i;

	if (!t)
		return (1);
	i = t->n_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&t->fork[i], NULL))
			return (2);
	}
	return (0);
}

int	receive_guests(t_table *t, int argc, char *argv[])
{
	if (init_table(t, argc, argv))
		return (1);
	if (t->n_philos < 2 || t->time_to_die < 0 || t->time_to_eat < 0
		|| t->time_to_sleep < 0 || t->n_philos > MAX_PHILO)
		return (printf("Parameters must be positive!!\n"), 2);
	if (init_philos(t))
		return (printf("Error while initializing philosophers!!\n"), 3);
	if (init_mutex(t))
		return (printf("Error while initializing mutexes!!\n"), 4);

	return (0);
}
