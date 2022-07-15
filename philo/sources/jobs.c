/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:53:28 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/15 13:47:27 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_start(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->n_philos == 1)
		return (dining_solo(table, philo));
	limit_startup(philo);
	while (table->is_all_alive
		&& table->count_total_meals != table->n_philos)
	{
		feed(table, philo);
		_sleep(table, philo);
		think(table, philo);
	}
	return (NULL);
}

static int	is_dead(t_table *t, t_philo *p)
{
	if (gen_timestamp() - p->ts_last_meal > t->time_to_die)
	{
		write_log(t, p, DEAD);
		t->is_all_alive = 0;
		return (1);
	}
	return (0);
}

static int	dead_or_full(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		if (is_dead(t, t->philo[i]))
			return (1);
		if (t->philo[i]->count_meals == t->n_meals
			&& !t->philo[i]->is_full)
		{
			t->count_total_meals++;
			t->philo[i]->is_full = 1;
		}
		if (t->count_total_meals == t->n_philos)
			return (1);
		i++;
	}
	return (0);
}

void	*logger_start(void *arg)
{
	t_table	*t;

	t = (t_table *)arg;
	while (t->is_all_alive)
	{
		if (dead_or_full(t))
			break ;
		usleep(1200);
	}
	return (NULL);
}
