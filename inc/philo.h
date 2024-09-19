/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:07:54 by allan             #+#    #+#             */
/*   Updated: 2024/09/19 04:45:27 by allan            ###   ########.fr       */
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

# define ERROR 1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# define NOT_DIGIT 0
# define DIGIT 2048

# define ERR_NBR_ARG "Error: The Number of Argument should be between 5 and 6\n"
# define ERR_ARG "Error: One or more Argument(s) is/are Invalid.\nError: Arguments need to be positive numeric and fit in a long int.\n"

enum e_state
{
	STATE_START,
	STATE_EAT,
	STATE_SLEEP,
	STATE_THINK,
	STATE_DIE
};

typedef struct	s_philo
{
	pthread_t		thread;
	enum e_state	state;
}				t_philo;

typedef struct	s_fork
{
	pthread_mutex_t	mutex;
	int				max_fork;
	int				available_fork;
}					t_fork;

typedef struct	s_args
{
	long long int		nbr_of_philo;
	long long int		time_to_die;
	long long int		time_to_eat;
	long long int		time_to_sleep;
	bool				fith_argument;
	long long int		nbr_of_meal;
}			t_args;


//philo
int		main(int argc, char **argv);

//philo_init
int		check_arg(char **argv);
int		init_arg(int argc, char **argv, t_args *argument);

//philo_utils
int		ft_isdigit(int c);
int		is_negative(long long int nbr);
long	ft_atoi(const char *nptr);
void	print_arg(t_args argument);

#endif