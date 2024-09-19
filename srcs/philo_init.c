/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 03:40:43 by allan             #+#    #+#             */
/*   Updated: 2024/09/19 04:43:45 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == NOT_DIGIT)
				return (ERROR);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	init_arg(int argc, char **argv, t_args *argument)
{
	argument->nbr_of_philo = ft_atoi(argv[1]);
	argument->time_to_die = ft_atoi(argv[2]);
	argument->time_to_eat = ft_atoi(argv[3]);
	argument->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		argument->fith_argument = 1;
		argument->nbr_of_meal = ft_atoi(argv[5]);
	}
	if (is_negative(argument->nbr_of_philo) == TRUE)
		return (ERROR);
	if (is_negative(argument->time_to_die) == TRUE)
		return (ERROR);
	if (is_negative(argument->time_to_eat) == TRUE)
		return (ERROR);
	if (is_negative(argument->time_to_sleep) == TRUE)
		return (ERROR);
	if (is_negative(argument->nbr_of_meal) == TRUE)
		return (ERROR);
	return (SUCCESS);
}
