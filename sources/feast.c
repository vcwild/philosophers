/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:32:05 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/09 02:53:48 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	feed(t_table *t, t_philo *p)
{
	pthread_mutex_lock(&t->fork[p->id_left_fork]);
	log(t, p, FORK);
	pthread_mutex_lock(&t->fork[p->id_right_fork]);
	log(t, p, FORK);
	pthread_mutex_lock(&t->feeder);
	log(t, p, EAT);
	p->ts_last_meal = gen_timestamp();
	pthread_mutex_unlock(&t->feeder);
	wait_for(t, t->time_to_eat);
	pthread_mutex_unlock(&t->fork[p->id_left_fork]);
	pthread_mutex_unlock(&t->fork[p->id_right_fork]);
	p->count_meals++;
}

void	rest(t_table *t, t_philo *p)
{
	log(t, p, SLEEP);
	wait_for(t, t->time_to_sleep);
	log(t, p, THINK);
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
		if (table->is_all_fed)
			break ;
		rest(table, philo);
	}
	return (NULL);
}

void check_alive(t_table *t)
{
	int	i;

	while (!t->is_all_fed && t->is_all_alive)
	{
		i = -1;
		while (++i < t->n_philos && t->is_all_alive)
		{
			pthread_mutex_lock(&t->feeder);
			if ((gen_timestamp() - t->philo[i].ts_last_meal) > t->time_to_die)
			{
				log(t, &t->philo[i], DEAD);
				t->is_all_alive = 0;
			}
			pthread_mutex_unlock(&t->feeder);
			usleep(100);
		}
		if (i == t->n_philos)
			t->is_all_fed = 1;
	}
}

int	gather_threads(t_table *t)
{
	int	i;
	int	status;

	i = -1;
	while (++i < t->n_philos)
	{
		status = pthread_join(t->philo[i].id_thread, NULL);
		if (status)
			return (status);
	}
	return (status);
}

int	feast(t_table *t)
{
	int	i;

	i = -1;
	t->ts_start = gen_timestamp();
	while (++i < t->n_philos)
	{
		if (pthread_create(&t->philo[i].id_thread, NULL, &thread_start, &t->philo[i]))
			return (printf("Error while creating threads\n"), 1);
		t->philo[i].ts_last_meal = gen_timestamp();
	}
	check_alive(t);
	if (gather_threads(t))
		return (printf("Error while joining threads\n"), 2);
	return (0);
}
