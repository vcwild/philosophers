/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:17:20 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/15 14:27:53 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static char	*read_status(t_philo_status status)
{
	if (status == EAT)
		return ("is eating");
	if (status == SLEEP)
		return ("is sleeping");
	if (status == THINK)
		return ("is thinking");
	if (status == DEAD)
		return ("died");
	if (status == FORK)
		return ("has taken a fork");
	return ("ERROR");
}

void	write_log(t_table *t, t_philo *p, t_philo_status status)
{
	if (t->is_all_alive)
	{
		printf("[%7lld] %i %s\n",
			gen_timestamp() - t->ts_start,
			p->id + 1,
			read_status(status));
	}
}

void	*dining_solo(t_table *t, t_philo *p)
{
	sem_wait(t->fork);
	write_log(t, p, FORK);
	sem_post(t->fork);
	write_log(t, p, DEAD);
	t->is_all_alive = 0;
	return (NULL);
}
