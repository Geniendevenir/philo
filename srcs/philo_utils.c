/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 02:22:15 by allan             #+#    #+#             */
/*   Updated: 2024/10/14 23:35:11 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	int		sign;
	long	nbr;

	nbr = 0;
	sign = 1;
	if (*nptr == '\0')
		return (0);
	while (*nptr && (*nptr == ' ' || *nptr == '\t'
			|| *nptr == '\n' || *nptr == '\r'
			|| *nptr == '\v' || *nptr == '\f'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = sign * -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = (nbr * 10) + (*nptr - '0');
		nptr++;
	}
	return (nbr * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (DIGIT);
	return (NOT_DIGIT);
}

int	is_valid_arg(long value, int type)
{
	if (type == ARG_PHILO)
	{
		if (value < 1 || value > 200)
			return (write(2, ERR_FIRST_ARG, 71), NOT_VALID);
	}
	else if (type == ARG_TIME)
	{
		if (value < 60 || value > INT_MAX)
			return (write(2, ERR_TIME_ARG, 67), NOT_VALID);
	}
	else if (type == ARG_MEAL)
	{
		if (value < 1 || value > INT_MAX)
			return (write(2, ERR_LAST_ARG, 72), NOT_VALID);
	}
	return (VALID);
}

void	error_msg(char *error)
{
	if (!error)
		return ;
	write(2, error, strlen(error));
}

void	print_arg(t_table table)
{
	printf("nbr_of_philo = %ld\n", table.nbr_of_philo);
	printf("time_to_die = %ld\n", table.time_to_die);
	printf("time_to_eat = %ld\n", table.time_to_eat);
	printf("time_to_sleep = %ld\n", table.time_to_sleep);
	if (table.meal_to_finish != -1)
		printf("nbr_of_meal = %ld\n", table.meal_to_finish);
}

void	print_table(t_philo *philo, t_table *table)
{
	long	i;

	i = 0;
	while (i < philo->table->nbr_of_philo)
	{
		printf("First Fork %ld <- Philo %ld -> Second Fork %ld\n", philo[i].first_fork->fork, philo[i].place, philo[i].second_fork->fork);
		printf("First Fork Address %p Mutex Address %p\n", (void *) &philo[i].first_fork->fork, (void *) &philo[i].first_fork->mutex);
		printf("Second Fork Address %p Mutex Address %p\n",(void *) &philo[i].second_fork->fork, (void *) &philo[i].second_fork->mutex);
		i++;
	}
	printf("\n");
	i = 0;
	printf("TABLE Mutex Address: %p\n", (void *) &table->mutex_table);
	while (i < philo->table->nbr_of_philo)
	{
		printf("Philo %ld Mutex Table Address: %p\n", philo[i].place, (void *) &philo[i].table->mutex_table);
		printf("Philo %ld Mutex Write Address: %p\n", philo[i].place, (void *) &philo[i].table->write_mutex);
		i++;
	}
}

void	write_status(e_status status, t_philo *philo)
{
	long	time;

	time = get_time(MILLISECOND) - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (status == FORK && !is_simulation_finished(philo->table))
		printf("%ld %ld has taken a fork\n", time, philo->place);
	else if (status == EATING && !is_simulation_finished(philo->table))
		printf("%ld %ld is eating\n", time, philo->place);
	else if (status == SLEEPING && !is_simulation_finished(philo->table))
		printf("%ld %ld is sleeping\n", time, philo->place);
	else if (status == THINKING && !is_simulation_finished(philo->table))
		printf("%ld %ld is thinking\n", time, philo->place);
	else if (status == DIED)
		printf("%ld %ld died\n", time, philo->place);
	else if (status == DEBUG)
		printf("%ld Tracker starts\n", time);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
