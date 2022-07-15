/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:40:52 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/15 13:47:21 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	feed(t_table *t, t_philo *p)
{
	pthread_mutex_lock(p->fork_left);
	pthread_mutex_lock(p->fork_right);
	write_log(t, p, FORK);
	write_log(t, p, FORK);
	p->ts_last_meal = gen_timestamp();
	write_log(t, p, EAT);
	p->count_meals++;
	usleep(t->time_to_eat * 1000);
	pthread_mutex_unlock(p->fork_left);
	pthread_mutex_unlock(p->fork_right);
}

void	_sleep(t_table *t, t_philo *p)
{
	write_log(t, p, SLEEP);
	usleep(t->time_to_sleep * 1000);
}

void	think(t_table *t, t_philo *p)
{
	write_log(t, p, THINK);
}

void	limit_startup(t_philo *p)
{
	if (p->id % 2)
	usleep(1500);
}
