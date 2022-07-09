/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:17:20 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/09 03:31:07 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	gen_timestamp(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

char	*read_status(t_philo_status action)
{
	if (action == EAT)
		return ("is eating");
	if (action == SLEEP)
		return ("is sleeping");
	if (action == THINK)
		return ("is thinking");
	if (action == DEAD)
		return ("died");
	if (action == FORK)
		return ("has taken a fork");
	return ("ERROR");
}

void	write_log(t_table *t, t_philo *p, t_philo_status action)
{
	pthread_mutex_lock(&t->logger);
	if (t->is_all_alive)
	{
		printf("[%lli] %i %s\n",
			gen_timestamp() - t->ts_start,
			p->id + 1,
			read_status(action));
	}
	pthread_mutex_unlock(&t->logger);
}

void	wait_for(t_table *t, long long time)
{
	long long	ts_start;

	ts_start = gen_timestamp();
	while (t->is_all_alive
		&& (gen_timestamp() - ts_start) < time)
		usleep(50);
}
