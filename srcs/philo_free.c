/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 01:52:30 by allan             #+#    #+#             */
/*   Updated: 2024/10/15 19:24:24 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo, t_fork *forks, t_table *table)
{
	pthread_mutex_destroy(&table->mutex_table);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&philo->mutex_philo);
	free_forks(forks, table->nbr_of_philo);
	free(philo);
}

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

void	error_join_threads(t_philo *philo, long to_join)
{
	long	i;

	i = 0;
	if (to_join <= 0)
		return ;
	while (i < to_join)
	{
		if (pthread_join(philo[i].thread, NULL) != SUCCESS)
			write(2, ERR_JOIN, strlen(ERR_JOIN));
		i++;
	}
}

void	join_threads(t_philo *philo, t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nbr_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != SUCCESS)
			write(2, ERR_JOIN, strlen(ERR_JOIN));
		i++;
	}
	if (pthread_join(table->track_end_simulation, NULL) != SUCCESS)
		write(2, ERR_JOIN, strlen(ERR_JOIN));
}
