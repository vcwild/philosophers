/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:32:05 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/15 14:32:19 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	create_threads(t_table *t)
{
	int	i;

	i = -1;
	t->ts_start = gen_timestamp();
	while (++i < t->n_philos)
	{
		if (pthread_create(&t->philo[i]->thread,
				NULL, thread_start, t->philo[i]))
			return (1);
	}
	if (pthread_create(&t->logger, NULL, logger_start, t))
		return (1);
	return (0);
}

static int	gather_threads(t_table *t)
{
	int	i;
	int	status;

	i = -1;
	while (++i < t->n_philos)
	{
		status = pthread_join(t->philo[i]->thread, NULL);
		if (status)
			return (status);
	}
	status = pthread_join(t->logger, NULL);
	return (status);
}

int	leave(t_table *t)
{
	int	i;

	i = -1;
	if (!t)
		return (1);
	while (++i < t->n_philos)
	{
		free(t->philo[i]);
	}
	sem_close(t->fork);
	sem_unlink("/fork");
	free(t->philo);
	return (0);
}

int	feast(t_table *t)
{
	if (create_threads(t))
		return (printf("Error while creating threads\n"), 1);
	if (gather_threads(t))
		return (printf("Error while joining threads\n"), 2);
	return (0);
}
