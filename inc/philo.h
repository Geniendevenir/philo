/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:07:54 by allan             #+#    #+#             */
/*   Updated: 2024/10/14 23:35:27 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>
#include <stdint.h>

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

# define ERR_NBR_ARG "Error: The Number of Argument should be between 5 and 6\n"
# define ERR_ARG "Error: One or more Argument(s) is/are Invalid.\nError: Arguments need to be positive numeric and fit in an int.\n"
# define ERR_SIZE_ARG "Error: Arguments need to fit in an int\n"
# define ERR_FIRST_ARG "Error: First Argument: Number of Philosopher needs to be > 0 && <= 200\n"
# define ERR_LAST_ARG "Error: Last Argument: Number of Meal needs to be >= 1 and fit in an int\n"
# define ERR_TIME_ARG "Error: Time Arguments: need to be positive, > 60 and fit in an int\n"
# define ERR_MALLOC_FORK "Error: Fork Malloc Allocation Failed\n"
# define ERR_MALLOC_PHILO "Error: PHILO Malloc Allocation Failed\n"
# define ERR_MUTEX_INIT "Error: Mutex Initialisation Failed\n"
# define ERR_PRINT "Error: Can't Print Table of more than 20 philosophers\n"
# define ERR_USEC "Error: Usex Paremeter is <= 0\n"
# define ERR_THREAD "Error: Pthread_create Initialisation Failed\n"
# define ERR_JOIN "Error: Pthread_join Initialisation Failed\n"
# define ERR_GET_TIME "Error: Get Time Initialisation Failed\n"
# define ERR_TIME_UNIT "Error: Wrong Type Unit Entered\n"

typedef struct s_table t_table;

typedef enum e_time_unit
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	e_time_unit;

typedef enum e_status
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	DEBUG
}	e_status;

typedef struct	s_fork
{
	long			fork;
	pthread_mutex_t	mutex;			//OK
}					t_fork;

typedef struct	s_philo
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
	pthread_mutex_t	mutex_table;		//OK
	pthread_mutex_t write_mutex;		//OK
	t_philo			*philo;
}				t_table;

//main
int		main(int argc, char **argv);

//philosopher
int		philosopher(t_philo *philo, t_fork *forks, t_table *table);
void	*dinning_alone(void *arg);
void	*cycle_of_life(void *arg);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);

//set
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	incr_long(pthread_mutex_t *mutex, long *dest);
bool	is_simulation_finished(t_table *table);
void	*set_simulation_finished(void *arg);

//philo_init
int		check_arg(char **argv);
int		init_table(int argc, char **argv, t_table *table);
int		init_fork(t_fork **forks, t_table *table);
int		init_philo(t_philo **philo, t_fork *forks, t_table *table);
void	assign_fork(t_philo *philo, t_fork *forks, long fork_nbr);

//philo_utils
int		ft_isdigit(int c);
int		is_valid_arg(long value, int type);
long	ft_atol(const char *nptr);
void	error_msg(char *error);
void	print_table(t_philo *philo, t_table *table);
void	print_arg(t_table table);
void	write_status(e_status status, t_philo *philo);

//philo_free
void	free_forks(t_fork *forks, long nbr_of_fork);
void	join_and_free(t_philo *philo, t_fork *forks, t_table *table);

//philo_time
long	get_elapsed_time_microseconds(struct timeval start, struct timeval end);
int		ft_usleep(long usec);
long	get_time(e_time_unit time_unit);
void	wait_everyone(pthread_mutex_t *mutex, t_table *table);
long	print_time(long start);


bool	is_philo_dead(t_philo *philo);
bool	wait_simulation_start(pthread_mutex_t *mutex, long *threads, long nbr_philo);
#endif