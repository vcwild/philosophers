/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:56:05 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/10 23:13:06 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* external headers */
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>

/* constants */
# define MAX_PHILO 200

/* structs */
typedef struct s_philo
{
	int				count_meals;
	bool			is_full;
	int				id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	long long		ts_last_meal;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	bool			is_all_fed;
	bool			is_all_alive;
	int				n_meals;
	int				count_total_meals;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		ts_start;
	pthread_t		logger;
	pthread_mutex_t	*fork;
	t_philo			**philo;
}					t_table;

typedef enum e_philo_status
{
	DEAD,
	EAT,
	FORK,
	SLEEP,
	THINK
}	t_philo_status;

/* startup */
int			receive_guests(t_table *t, int argc, char *argv[]);

/* thread callbacks */
void		*logger_start(void *arg);
void		*thread_start(void *arg);

/* execution */
int			feast(t_table *t);

/* utils */
int			ft_atoi(const char *str);
void		write_log(t_table *t, t_philo *p, t_philo_status action);
long long	gen_timestamp(void);
void		*dining_solo(t_table *t, t_philo *p);

#endif
