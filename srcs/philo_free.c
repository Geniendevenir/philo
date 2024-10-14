/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 01:52:30 by allan             #+#    #+#             */
/*   Updated: 2024/10/13 16:33:49 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_fork *forks, long nbr_of_fork)
{
	long	i;

	i = 0;
	while (i < nbr_of_fork)
	{
		pthread_mutex_destroy((&forks[i].mutex));
		i++;
	}
	free(forks);
	return ;
}

void	join_and_free(t_philo *philo, t_fork *forks, t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nbr_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != SUCCESS)
			write(2,ERR_JOIN, 42);
		i++;
	}
	if (pthread_join(table->track_end_simulation, NULL) != SUCCESS)
		write(2,ERR_JOIN, 42);
	free_forks(forks, table->nbr_of_philo);
	free(philo);
}
