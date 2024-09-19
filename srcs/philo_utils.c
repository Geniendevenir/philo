/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 02:22:15 by allan             #+#    #+#             */
/*   Updated: 2024/09/19 04:41:55 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *nptr)
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

int	is_negative(long long int nbr)
{
	if (nbr < 0)
		return (TRUE);
	return (FALSE);
}

void	print_arg(t_args argument)
{
	printf("nbr_of_philo = %lld\n", argument.nbr_of_philo);
	printf("time_to_die = %lld\n", argument.time_to_die);
	printf("time_to_eat = %lld\n", argument.time_to_eat);
	printf("time_to_sleep = %lld\n", argument.time_to_sleep);
	if (argument.fith_argument == 1)
		printf("nbr_of_meal = %lld\n", argument.nbr_of_meal);
}
