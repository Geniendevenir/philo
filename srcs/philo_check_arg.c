/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:12:03 by adebert           #+#    #+#             */
/*   Updated: 2024/10/16 12:51:22 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
				return (error_msg(ERR_ARG), ERROR);
			j++;
		}
		if (i == ARG_PHILO && j > 3)
			return (error_msg(ERR_FIRST_ARG), ERROR);
		else if (i == ARG_MEAL && j > 10)
			return (error_msg(ERR_LAST_ARG), ERROR);
		else if (j > 10)
			return (error_msg(ERR_SIZE_ARG), ERROR);
		i++;
	}
	return (SUCCESS);
}

int	is_valid_arg(long value, int type)
{
	if (type == ARG_PHILO)
	{
		if (value < 1 || value > 200)
			return (error_msg(ERR_FIRST_ARG), NOT_VALID);
	}
	else if (type == ARG_TIME)
	{
		if (value < 60 || value > INT_MAX)
			return (error_msg(ERR_TIME_ARG), NOT_VALID);
	}
	else if (type == ARG_MEAL)
	{
		if (value < 1 || value > INT_MAX)
			return (error_msg(ERR_LAST_ARG), NOT_VALID);
	}
	return (VALID);
}
