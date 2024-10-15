/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:05:54 by allan             #+#    #+#             */
/*   Updated: 2024/10/15 19:24:21 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_fork	*forks;
	t_philo	*philo;

	forks = NULL;
	philo = NULL;
	if (argc < 5 || argc > 6)
		return (write(1, ERR_NBR_ARG, 56), 1);
	if (check_arg(argv) == ERROR)
		return (ERROR);
	if (init_table(argc, argv, &table) == ERROR)
		return (ERROR);
	if (init_fork(&forks, &table) == ERROR)
		return (ERROR);
	if (init_philo(&philo, forks, &table) == ERROR)
		return (ERROR);
	if (philosopher(philo, forks, &table) == ERROR)
		return (ERROR);
	return (0);
}
