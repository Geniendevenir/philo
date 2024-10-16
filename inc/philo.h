/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:35:31 by adebert           #+#    #+#             */
/*   Updated: 2024/10/16 13:07:13 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <stdint.h>

# define ERROR 1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# define VALID 0
# define NOT_VALID 1
# define DIGIT 2048
# define NOT_DIGIT 0
# define DEATH 1
# define ARG_PHILO 1
# define ARG_TIME 2
# define ARG_MEAL 5

# define ERR_NBR_ARG "Error: Number of Argument should be between 5 and 6\n"
# define ERR_ARG "Error: Invalid Argument. Need to be: > 0 && < INT_MAX\n"
# define ERR_SIZE_ARG "Error: Arguments need to fit in an int\n"
# define ERR_FIRST_ARG "Error: Nbr of Philosopher needs to be > 0 && <= 200\n"
# define ERR_LAST_ARG "Error: Number of Meal needs to be > 0 && < INT_MAX\n"
# define ERR_TIME_ARG "Error: Time Arguments need to be: >= 60 && < INT_MAX\n"
# define ERR_MALLOC_FORK "Error: Fork Malloc Allocation Failed\n"
# define ERR_MALLOC_PHILO "Error: PHILO Malloc Allocation Failed\n"
# define ERR_MUTEX_INIT "Error: Mutex Initialisation Failed\n"
# define ERR_PRINT "Error: Can't Print Table of more than 20 philosophers\n"
# define ERR_USEC "Error: Usex Paremeter is <= 0\n"
# define ERR_THREAD "Error: Pthread_create Initialisation Failed\n"
# define ERR_JOIN "Error: Pthread_join Initialisation Failed\n"
# define ERR_GET_TIME "Error: Get Time Initialisation Failed\n"
# define ERR_TIME_UNIT "Error: Wrong Type Unit Entered\n"

typedef struct s_table	t_table;

typedef enum e_time_unit
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time_unit;

typedef enum e_status
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	DEBUG
}	t_status;

typedef struct s_fork
{
	long			fork;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	long			place;
	bool			is_full;
	long			last_meal;
	long			meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread;
	pthread_mutex_t	mutex_philo;
	t_table			*table;

}				t_philo;

typedef struct s_table
{
	long			nbr_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_to_finish;
	long			start_simulation;
	bool			end_simulation;
	bool			is_everyone_ready;
	bool			is_someone_dead;
	long			philo_full;
	long			nbr_philo_ready;
	pthread_t		track_end_simulation;
	pthread_mutex_t	mutex_table;
	pthread_mutex_t	write_mutex;
	t_philo			*philo;
}				t_table;

//main
int		main(int argc, char **argv);

//philosopher
int		philosopher(t_philo *philo, t_fork *forks, t_table *table);
void	*cycle_of_life(void *arg);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo, bool status_msg);

//philo_alone
void	*dinning_alone(void *arg);

//philo_set_get
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	incr_long(pthread_mutex_t *mutex, long *dest);

//philo_finish
bool	is_philo_dead(t_philo *philo);
bool	is_simulation_finished(t_table *table);
void	*set_simulation_finished(void *arg);

//philo_check_arg
int		check_arg(char **argv);
int		is_valid_arg(long value, int type);

//philo_init_arg
int		init_table(int argc, char **argv, t_table *table);
int		init_table_arg(int argc, char **argv, t_table *table);
int		init_fork(t_fork **forks, t_table *table);
int		init_philo(t_philo **philo, t_fork *forks, t_table *table);
void	assign_fork(t_philo *philo, t_fork *forks, long fork_nbr);

//philo_init_threads
bool	init_single_thread(t_philo *philo, t_fork *forks, t_table *table);
bool	init_mutli_threads(t_philo *philo, t_fork *forks, t_table *table);

//philo_utils
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
long	ft_atol(const char *nptr);
void	error_msg(char *error);
void	write_status(t_status status, t_philo *philo);

//philo_free
void	free_all(t_philo *philo, t_fork *forks, t_table *table);
void	free_forks(t_fork *forks, long nbr_of_fork);
void	error_join_threads(t_philo *philo, long to_join);
void	join_threads(t_philo *philo, t_table *table);

//philo_time
long	get_elapsed_time_microseconds(struct timeval start, struct timeval end);
int		ft_usleep(long usec);
long	get_time(t_time_unit time_unit);
void	wait_everyone(pthread_mutex_t *mutex, t_table *table);
long	print_time(long start);

//philo_sync
bool	wait_simulation_start(pthread_mutex_t *mutex,
			long *threads, long nbr_philo);
void	desynchronize_philo(t_philo *philo);
#endif