/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:05:54 by allan             #+#    #+#             */
/*   Updated: 2024/10/16 12:48:53 by adebert          ###   ########.fr       */
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
		return (error_msg(ERR_NBR_ARG), ERROR);
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
