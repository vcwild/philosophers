/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:56:05 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/08 01:31:00 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define MAX_PHILO 250

typedef struct		s_philo
{
	int				count_meals;
	int				id;
	int				id_left_fork;
	int				id_right_fork;
	long long		ts_last_meal;
	pthread_t		id_thread;
}					t_philo;

typedef struct		s_table
{
	int				n_meals;
	int				n_philos;
	int				philo_alive;
	int				philo_feeding;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		ts_start;
	pthread_mutex_t	fork[MAX_PHILO];
	t_philo			philo[MAX_PHILO];
}					t_table;

/* startup */
int			init_program(t_table *t, int argc, char *argv[]);

/* utils */
int			ft_atoi(const char *str);

#endif
