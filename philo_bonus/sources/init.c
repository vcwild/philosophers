/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:57:41 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/15 16:30:01 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_table(t_table *t, int argc, char *argv[])
{
	t->n_philos = ft_atoi(argv[1]);
	t->philo = (t_philo **)malloc(sizeof(t_philo *) * t->n_philos);
	if (!t->fork || !t->philo)
		return (1);
	t->time_to_die = ft_atoi(argv[2]);
	t->time_to_eat = ft_atoi(argv[3]);
	t->time_to_sleep = ft_atoi(argv[4]);
	t->ts_start = gen_timestamp();
	t->is_all_alive = 1;
	t->is_all_fed = 0;
	t->count_total_meals = 0;
	t->n_meals = -1;
	if (argc == 6)
		t->n_meals = ft_atoi(argv[5]);
	return (0);
}

static int	init_philos(t_table *t)
{
	int		i;
	t_philo	*philo;

	if (!t)
		return (1);
	i = t->n_philos;
	while (--i >= 0)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (2);
		philo->id = i;
		philo->count_meals = 0;
		philo->fork_left = t->fork + i;
		philo->fork_right = t->fork + ((i + 1) % t->n_philos);
		philo->ts_last_meal = t->ts_start;
		philo->thread = 0;
		philo->is_full = 0;
		philo->table = t;
		t->philo[i] = philo;
	}
	return (0);
}

static int	init_sem(t_table *t)
{
	if (!t)
		return (1);
	sem_unlink("/fork");
	t->fork = sem_open("/fork", O_CREAT, S_IRWXU, t->n_philos);
	sem_init
	return (0);
}

int	receive_guests(t_table *t, int argc, char *argv[])
{
	if (init_table(t, argc, argv))
		return (1);
	if (init_philos(t))
		return (printf("Error while initializing philosophers!!\n"), 3);
	if (init_sem(t))
		return (printf("Error while initializing semaphores!!\n"), 4);
	return (0);
}
