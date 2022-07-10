/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:53:28 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/09 23:53:34 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	feed(t_table *t, t_philo *p)
{
	pthread_mutex_lock(&t->fork[p->id_left_fork]);
	write_log(t, p, FORK);
	pthread_mutex_lock(&t->fork[p->id_right_fork]);
	write_log(t, p, FORK);
	write_log(t, p, EAT);
	p->ts_last_meal = gen_timestamp();
	usleep(t->time_to_eat * 1000);
	pthread_mutex_unlock(&t->fork[p->id_left_fork]);
	pthread_mutex_unlock(&t->fork[p->id_right_fork]);
	p->count_meals++;
}

void	*thread_start(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2)
		usleep(15000);
	while (table->is_all_alive)
	{
		feed(table, philo);
		write_log(table, philo, SLEEP);
		usleep(table->time_to_sleep * 1000);
		write_log(table, philo, THINK);
	}
	return (NULL);
}

static int	is_dead(t_table *t, t_philo *p)
{
	if (gen_timestamp() - p->ts_last_meal)
	{
		t->is_all_alive = 0;
		write_log(t, p, DEAD);
		return (1);
	}
	return (0);
}

static int	dead_or_full(t_table *t)
{
	int		i;

	i = 0;
	while (i < t->n_philos)
	{
		if (is_dead(t, &t->philo[i]))
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
