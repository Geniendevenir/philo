/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:12:03 by adebert           #+#    #+#             */
/*   Updated: 2024/10/15 19:24:25 by adebert          ###   ########.fr       */
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
				return (write(2, ERR_ARG, 111), ERROR);
			j++;
		}
		if (i == ARG_PHILO && j > 3)
			return (write(2, ERR_FIRST_ARG, 71), ERROR);
		else if (i == ARG_MEAL && j > 10)
			return (write(2, ERR_LAST_ARG, 72), ERROR);
		else if (j > 10)
			return (write(2, ERR_SIZE_ARG, 39), ERROR);
		i++;
	}
	return (SUCCESS);
}
