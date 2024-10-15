/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:07:19 by allan             #+#    #+#             */
/*   Updated: 2024/10/15 19:18:13 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher(t_philo *philo, t_fork *forks, t_table *table)
{
	long	i;

	i = 0;
	if (table->meal_to_finish == 0)
		return (free_all(philo, forks, table), SUCCESS);
	if (table->nbr_of_philo == 1)
	{
		if (pthread_create((&philo[i].thread), NULL, dinning_alone, &philo[i]) == ERROR)
			return (free_all(philo, forks, table), write(2, ERR_THREAD, strlen(ERR_THREAD)), ERROR);
	}
	else
	{
		while (i < table->nbr_of_philo)
		{
			if (pthread_create((&philo[i].thread), NULL, cycle_of_life, &philo[i]) == ERROR)
				return (error_join_threads(philo, i - 1),
					free_all(philo, forks, table),
					write(2, ERR_THREAD, strlen(ERR_THREAD)), ERROR);
			i++;
		}
	}
	if (pthread_create((&table->track_end_simulation), NULL, set_simulation_finished, table) == ERROR)
		return (error_join_threads(philo, i),
			free_all(philo, forks, table),
			write(2, ERR_THREAD, strlen(ERR_THREAD)), ERROR);
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->mutex_table, &table->is_everyone_ready, TRUE);
	join_threads(philo, table);
	free_all(philo, forks, table);
	return (SUCCESS);
}

void	*cycle_of_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	wait_everyone(&philo->table->mutex_table, philo->table);
	set_long(&philo->mutex_philo, &philo->last_meal, get_time(MILLISECOND));
	incr_long(&philo->table->mutex_table, &philo->table->nbr_philo_ready);
	desynchronize_philo(philo);
	while (is_simulation_finished(philo->table) == FALSE)
	{
		if (philo->table->meal_to_finish > 0
			&& philo->meal == philo->table->meal_to_finish)
			incr_long(&philo->table->mutex_table, &philo->table->philo_full);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo, 1);
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock((&philo->first_fork->mutex));
	write_status(FORK, philo);
	pthread_mutex_lock((&philo->second_fork->mutex));
	write_status(FORK, philo);
	set_long(&philo->mutex_philo, &philo->last_meal, get_time(MILLISECOND));
	write_status(EATING, philo);
	ft_usleep(philo->table->time_to_eat);
	philo->meal += 1;
	if (philo->table->meal_to_finish > 0
		&& philo->table->meal_to_finish == philo->meal)
		set_bool(&philo->mutex_philo, &philo->is_full, TRUE);
	if (philo->meal == philo->table->meal_to_finish)
		set_bool(&philo->mutex_philo, &philo->is_full, TRUE);
	pthread_mutex_unlock((&philo->second_fork->mutex));
	pthread_mutex_unlock((&philo->first_fork->mutex));
}

void	ft_sleep(t_philo *philo)
{
	long	start;
	long	end;

	write_status(SLEEPING, philo);
	start = get_time(MILLISECOND);
	ft_usleep(philo->table->time_to_sleep);
	end = get_time(MILLISECOND);
}

void	ft_think(t_philo *philo, bool status_msg)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	if (status_msg == 1)
		write_status(THINKING, philo);
	if (philo->table->nbr_of_philo % 2 == 0)
		return ;
	else if (philo->table->nbr_of_philo % 2 != 0)
	{
		time_eat = philo->table->time_to_eat;
		time_sleep = philo->table->time_to_sleep;
		time_think = (time_eat * 2) - time_sleep;
		if (time_think < 0)
			time_think = 0;
		ft_usleep(time_think * 0.42);
	}
}
