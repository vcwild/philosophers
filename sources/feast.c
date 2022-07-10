/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:32:05 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/09 23:50:00 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_table *t)
{
	int	i;

	i = -1;
	t->ts_start = gen_timestamp();
	while (++i < t->n_philos)
	{
		if (pthread_create(&t->philo[i]->id_thread,
				NULL, &thread_start, &t->philo[i]))
			return (1);
	}
	if (pthread_create(&t->logger, NULL, &logger_start, &t))
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
		status = pthread_join(t->philo[i]->id_thread, NULL);
		if (status)
			return (status);
	}
	status = pthread_join(t->logger, NULL);
	return (status);
}

int	feast(t_table *t)
{
	if (create_threads(t))
		return (printf("Error while creating threads\n"), 1);
	if (gather_threads(t))
		return (printf("Error while joining threads\n"), 2);
	return (0);
}
