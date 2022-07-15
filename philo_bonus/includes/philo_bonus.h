/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:56:05 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/15 14:24:41 by vwildner         ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>

/* constants */

# define MAX_PHILO 200

/* structs */

/**
 * @brief	The struct representing a philosopher.
 */
typedef struct s_philo
{
	int				count_meals;
	bool			is_full;
	int				id;
	sem_t			*fork_left;
	sem_t			*fork_right;
	long long		ts_last_meal;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

/**
 * @brief	The struct representing the table.
 */
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
	sem_t			*fork;
	t_philo			**philo;
}					t_table;

/**
 * @brief	The status of the philosopher.
 */
typedef enum e_philo_status
{
	DEAD,
	EAT,
	FORK,
	SLEEP,
	THINK
}	t_philo_status;

/* startup */

/**
 * @brief Recieves guests at the table. Starts the table, the philosophers and the logger.
 *
 * @param t		The table.
 * @param argc	The number of arguments.
 * @param argv	The arguments.
 * @return int	0 if everything went well, > 0 otherwise.
 */
int			receive_guests(t_table *t, int argc, char *argv[]);

/* statuss */

/**
 * @brief	The function that makes the philosophers eat.
 *
 * @param t	The table.
 * @param p	The philosopher.
 */

void		feed(t_table *t, t_philo *p);
/**
 * @brief The function that makes the philosophers sleep.
 *
 * @param t	The table.
 * @param p	The philosopher.
 */
void		_sleep(t_table *t, t_philo *p);

/**
 * @brief	The function that makes the philosophers think.
 *
 * @param t	The table.
 * @param p	The philosopher.
 */
void		think(t_table *t, t_philo *p);

/* thread callbacks */
/**
 * @brief			The logger thread callback routine.
 *
 * @param arg		The table.
 * @return void* Returns NULL.
 */

void		*logger_start(void *arg);
/**
 * @brief			The philosopher's thread callback routine.
 *
 * @param arg		The philosopher.
 * @return void* Returns NULL.
 */
void		*thread_start(void *arg);

/* execution */
/**
 * @brief		The main program routine to start and execute threads.
 *
 * @param t		The table.
 * @return int Returns 0 if everything went well, > 0 otherwise.
 */
int			feast(t_table *t);

/* teardown */
/**
 * @brief		Destroys down the table and the philosophers.
 *
 * @param t		The table.
 * @return int Returns 0 if everything went well, > 0 otherwise.
 */
int	leave(t_table *t);

/* utils */

/**
 * @brief		Verifies if the inputs from the user are valid.
 *
 * @param argc	The number of arguments.
 * @param argv	The arguments.
 * @return int 0 if everything went well, > 0 otherwise.
 */
int			check_inputs(int argc, char *argv[]);

/**
 * @brief	Transforms a string of characters into an integer.
 * 			Parses the inputs from the user from the command line.
 *
 * @param str	The string to be parsed.
 * @return int The integer representation of the string.
 */
int			ft_atoi(const char *str);

/**
 * @brief Writes to the standard output the message corresponding to the status of the philosopher.
 *
 * @param t			The table.
 * @param p			The philosopher.
 * @param status	The status to be reported.
 */
void		write_log(t_table *t, t_philo *p, t_philo_status status);

/**
 * @brief	Generates a timestamp in milliseconds.
 *
 * @return long long The timestamp.
 */
long long	gen_timestamp(void);

/**
 * @brief	Executes a deterministic routine if the philosopher is dining all alone.
 *
 * @param t	The table.
 * @param p	The philosopher.
 * @return void* Returns NULL.
 */
void		*dining_solo(t_table *t, t_philo *p);

/**
 * @brief	Limits the threads with even ids so it does not start at the same time.
 *
 * @param p	The philosopher.
 */
void		limit_startup(t_philo *p);
#endif
