/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:40:52 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/15 14:27:38 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	feed(t_table *t, t_philo *p)
{
	sem_wait(t->fork);
	sem_wait(t->fork);
	write_log(t, p, FORK);
	write_log(t, p, FORK);
	p->ts_last_meal = gen_timestamp();
	write_log(t, p, EAT);
	p->count_meals++;
	usleep(t->time_to_eat * 1000);
	sem_post(t->fork);
	sem_post(t->fork);
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
