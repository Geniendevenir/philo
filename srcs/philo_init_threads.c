/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:28:44 by adebert           #+#    #+#             */
/*   Updated: 2024/10/16 12:54:07 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	init_single_thread(t_philo *philo, t_fork *forks, t_table *table)
{
	long	i;

	i = 0;
	if (pthread_create((&philo[i].thread),
			NULL, dinning_alone, &philo[i]) == ERROR)
	{
		free_all(philo, forks, table);
		return (error_msg(ERR_THREAD), ERROR);
	}
	return (SUCCESS);
}

bool	init_mutli_threads(t_philo *philo, t_fork *forks, t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nbr_of_philo)
	{
		if (pthread_create((&philo[i].thread),
				NULL, cycle_of_life, &philo[i]) == ERROR)
		{
			error_join_threads(philo, i - 1);
			free_all(philo, forks, table);
			return (error_msg(ERR_THREAD), ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
