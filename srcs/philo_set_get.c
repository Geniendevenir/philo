/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:04:15 by allan             #+#    #+#             */
/*   Updated: 2024/10/15 15:50:02 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
		*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	get;
	pthread_mutex_lock(mutex);
		get = *value;
	pthread_mutex_unlock(mutex);
	return (get);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
		*dest = value;
	pthread_mutex_unlock(mutex);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	get;
	pthread_mutex_lock(mutex);
		get = *value;
	pthread_mutex_unlock(mutex);
	return (get);
}

void	incr_long(pthread_mutex_t *mutex, long *dest)
{
	pthread_mutex_lock(mutex);
		(*dest)++;
	pthread_mutex_unlock(mutex);
}

bool	is_simulation_finished(t_table *table)
{
	return(get_bool(&table->mutex_table, &table->end_simulation));
}

bool	is_philo_dead(t_philo *philo)
{
	long	elapsed;

	/* if (get_bool(&philo->mutex_philo, &philo->is_full) == TRUE)
		return (FALSE); */
	elapsed = get_time(MILLISECOND) - get_long(&philo->mutex_philo, &philo->last_meal);
	//printf("elapsed/time_to_die: %ld / %ld\n", elapsed, philo->table->time_to_die);
	if (elapsed > (philo->table->time_to_die / 1000))
	{
		/* printf("%ld died after %ld miliseconds\n", philo->place, elapsed);
		printf("elpased = %ld\n", elapsed);
		printf("last meal = %ld\n", get_long(&philo->mutex_philo, &philo->last_meal)); */
		return (TRUE);
	}
	else
		return (FALSE);
}

bool	wait_simulation_start(pthread_mutex_t *mutex, long *threads, long nbr_philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == nbr_philo)
	{
		/* printf("nbr_threads ready %ld\n", *threads);
		printf("nbr_philo %ld\n", nbr_philo); */
		ret = true;
	}
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	*set_simulation_finished(void *arg)
{
	t_table			*table;
	int				i;

	table = (t_table *)arg;
	//printf("NEW TABLE Mutex Address: %p\n", (void *) &table->mutex_table);
	while (wait_simulation_start(&table->mutex_table,
		&table->nbr_philo_ready, table->nbr_of_philo) == FALSE || table->start_simulation == 0)
		;
	//write_status(DEBUG, table->philo);
	while (is_simulation_finished(table) == FALSE)
	{
		i = 0;
		//check if everyone is full
		if (table->meal_to_finish > 0 && table->nbr_of_philo == table->philo_full)
		{
			set_bool(&table->mutex_table, &table->end_simulation, TRUE);
			//printf("Everyone is full\n");
		}
		//	check if philo died
		while (i < table->nbr_of_philo && is_simulation_finished(table) == FALSE)
		{
			if (is_philo_dead(table->philo + i) == TRUE)
			{
				set_bool(&table->mutex_table, &table->end_simulation, TRUE);
				write_status(DIED, table->philo + i);
			}
			i++;
		}
	}
	return (NULL);
}
