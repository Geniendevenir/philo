/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:07:19 by allan             #+#    #+#             */
/*   Updated: 2024/10/15 00:05:45 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	PROBLEMS:

	II -	No Condition to stop simulation when a philo dies
	III -	Death timer is not checked during sleep
	V -		Still dont know when to join or detach threads -> Just Join
	VII -	If philo has eaten arg->nbr_meal stop simulation immediatly
	IX -	Add case for 1 philo he should die

	I -		Only one philo eat at a time: Not Opti								OK
	IV -	Threads dont wait for each other befre starting the simulation		OK
	X -		Recheck nbr_meal can be 0 just return ;								OK
	VI -	Recheck input (philo <= 200, Time >= 60)							OK
	VIII -	Change timer to show since the beggining of the simulation			OK
*/


/*
	HANDLE MEALS: Create a thread in table that will track if everyone is full or someone is dead

	I -		Add tracker_full a thread to the table
	II -	If 5th arguemtn > 0 Initiate the tracker with pthread
	III -	Create function tracker_meal_to_finish
	IV -	Wait for everyone to start
	V -		Loop while !simulation_finished
	VI -	Check if table->philo_full == table->meal_to_finish
*/
void	*dinning_alone(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	wait_everyone(&philo->table->mutex_table, philo->table);
	set_long(&philo->mutex_philo, &philo->last_meal, get_time(MILLISECOND));
	incr_long(&philo->table->mutex_table, &philo->table->nbr_philo_ready);
	write_status(FORK, philo);
	while (is_simulation_finished(philo->table) == FALSE)
		;
	return (NULL);
}


int	philosopher(t_philo *philo, t_fork *forks, t_table *table)
{
	long	i;

	i = 0;
	if (table->meal_to_finish == 0)
	{
		free_forks(forks, table->nbr_of_philo);
		free(philo);
		return (0);
	}
	if (table->nbr_of_philo == 1)
	{
		if (pthread_create((&philo[i].thread), NULL, dinning_alone, &philo[i]) == ERROR)
		{
			free_forks(forks, table->nbr_of_philo);
			free(philo);
			return (write(2, ERR_THREAD, 44), ERROR);
		}
	}
	else
	{
		while (i < table->nbr_of_philo)
		{
			if (pthread_create((&philo[i].thread), NULL, cycle_of_life, &philo[i]) == ERROR)
			{
				free_forks(forks, table->nbr_of_philo);
				free(philo);
				return (write(2, ERR_THREAD, 44), ERROR);
			}
			i++;
		}
		//tracker_simulation is finished;
	}
	if (pthread_create((&table->track_end_simulation), NULL, set_simulation_finished, table) == ERROR)
	{
		free_forks(forks, table->nbr_of_philo);
		free(philo);
		return (write(2, ERR_THREAD, 44), ERROR);
	}
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->mutex_table, &table->is_everyone_ready, TRUE);
	//join
	join_and_free(philo, forks, table);
	return (SUCCESS);
}

void	*cycle_of_life(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	wait_everyone(&philo->table->mutex_table, philo->table);
	set_long(&philo->mutex_philo, &philo->last_meal, get_time(MILLISECOND));
	incr_long(&philo->table->mutex_table, &philo->table->nbr_philo_ready);
	
	while (is_simulation_finished(philo->table) == FALSE)
	{
		//is_full?
		if (philo->table->meal_to_finish > 0
			&& philo->meal == philo->table->meal_to_finish)
		{
			incr_long(&philo->table->mutex_table, &philo->table->philo_full);
			printf("%ld is full after %ld meals\n", philo->place, philo->meal);
		}
		//eat
		ft_eat(philo);
		//sleep
		ft_sleep(philo);
		//think
		ft_think(philo);
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	/* long	start;
	long	end; */

	pthread_mutex_lock((&philo->first_fork->mutex));
	write_status(FORK, philo);
	//printf("Philo %ld fork %ld\n", philo->place, philo->first_fork->fork);
	//printf("First Mutex address: %p\n", (void *)&philo->first_fork->mutex);
	pthread_mutex_lock((&philo->second_fork->mutex));
	write_status(FORK, philo);
	//printf("Philo %ld fork %ld\n", philo->place, philo->second_fork->fork);
	//printf("Second Mutex address: %p\n", (void *)&philo->second_fork->mutex);
	set_long(&philo->mutex_philo, &philo->last_meal, get_time(MILLISECOND));
	write_status(EATING, philo);
	//start = get_time(MILLISECOND);
	ft_usleep(philo->table->time_to_eat);
	//end = get_time(MILLISECOND);
	philo->meal += 1;
	//printf("%ld ate %ld meals\n", philo->place, philo->meal);
	if (philo->table->meal_to_finish > 0
		&& philo->table->meal_to_finish == philo->meal)
		set_bool(&philo->mutex_philo, &philo->is_full, TRUE);
	//printf("%ld ate in %ld\n", philo->place, end - start);
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
	printf("%ld sleept for %ld\n", philo->place, end - start);
}

void	ft_think(t_philo *philo)
{
	write_status(THINKING, philo);
	//add fairness
}
