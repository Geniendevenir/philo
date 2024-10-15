/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 02:22:15 by allan             #+#    #+#             */
/*   Updated: 2024/10/15 19:19:41 by adebert          ###   ########.fr       */
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
