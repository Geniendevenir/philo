/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 03:40:43 by allan             #+#    #+#             */
/*   Updated: 2024/10/15 19:24:24 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(int argc, char **argv, t_table *table)
{
	if (is_valid_arg(ft_atol(argv[1]), ARG_PHILO) == NOT_VALID)
		return (ERROR);
	else if (is_valid_arg(ft_atol(argv[2]), ARG_TIME) == NOT_VALID)
		return (ERROR);
	else if (is_valid_arg(ft_atol(argv[3]), ARG_TIME) == NOT_VALID)
		return (ERROR);
	else if (is_valid_arg(ft_atol(argv[4]), ARG_TIME) == NOT_VALID)
		return (ERROR);
	if (init_table_arg(argc, argv, table) == ERROR)
		return (ERROR);
	if (pthread_mutex_init(&table->mutex_table, NULL) != SUCCESS)
		return (write(2, ERR_MUTEX_INIT, 35), ERROR);
	if (pthread_mutex_init(&table->write_mutex, NULL) != SUCCESS)
	{
		pthread_mutex_destroy(&table->mutex_table);
		return (write(2, ERR_MUTEX_INIT, 35), ERROR);
	}
	return (SUCCESS);
}

int	init_table_arg(int argc, char **argv, t_table *table)
{
	table->nbr_of_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	table->meal_to_finish = -1;
	if (argc == 6)
	{
		if (is_valid_arg(ft_atol(argv[5]), ARG_MEAL) == NOT_VALID)
			return (ERROR);
		else
			table->meal_to_finish = ft_atol(argv[5]);
	}
	table->start_simulation = 0;
	table->end_simulation = 0;
	table->is_someone_dead = FALSE;
	table->is_everyone_ready = FALSE;
	table->philo_full = 0;
	table->nbr_philo_ready = 0;
	return (SUCCESS);
}

int	init_fork(t_fork **forks, t_table *table)
{
	long	i;

	i = 0;
	*forks = malloc(sizeof(t_fork) * table->nbr_of_philo);
	if (!(*forks))
	{
		pthread_mutex_destroy(&table->mutex_table);
		pthread_mutex_destroy(&table->write_mutex);
		return (write(1, ERR_MALLOC_FORK, 37), ERROR);
	}
	while (i < table->nbr_of_philo)
	{
		(*forks)[i].fork = i;
		if (pthread_mutex_init((&(*forks)[i].mutex), NULL) == ERROR)
		{
			free_forks(*forks, i);
			pthread_mutex_destroy(&table->mutex_table);
			pthread_mutex_destroy(&table->write_mutex);
			return (write(2, ERR_MUTEX_INIT, 35), ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_philo(t_philo **philo, t_fork *forks, t_table *table)
{
	long	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * table->nbr_of_philo);
	if (!*philo)
	{
		free_forks(forks, table->nbr_of_philo);
		pthread_mutex_destroy(&table->mutex_table);
		pthread_mutex_destroy(&table->write_mutex);
		return (write(2, ERR_MALLOC_PHILO, 38), ERROR);
	}
	table->philo = *philo;
	while (i < table->nbr_of_philo)
	{
		(*philo)[i].place = i + 1;
		(*philo)[i].is_full = FALSE;
		(*philo)[i].last_meal = 0;
		(*philo)[i].meal = 0;
		(*philo)[i].table = table;
		assign_fork(&(*philo)[i], forks, i);
		pthread_mutex_init(&(*philo)[i].mutex_philo, NULL); //secure that
		i++;
	}
	return (0);
}

void	assign_fork(t_philo *philo, t_fork *forks, long fork_nbr)
{
	if (philo->place % 2 == 0)
	{
		philo->first_fork = &forks[fork_nbr];
		if (philo->place == philo->table->nbr_of_philo)
			philo->second_fork = &forks[0];
		else
			philo->second_fork = &forks[fork_nbr + 1];
	}
	else
	{
		if (philo->place == philo->table->nbr_of_philo)
			philo->first_fork = &forks[0];
		else
			philo->first_fork = &forks[fork_nbr + 1];
		philo->second_fork = &forks[fork_nbr];
	}
}
