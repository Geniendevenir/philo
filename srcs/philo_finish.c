/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:57:26 by adebert           #+#    #+#             */
/*   Updated: 2024/10/15 19:17:19 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	is_philo_dead(t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND)
		- get_long(&philo->mutex_philo, &philo->last_meal);
	if (elapsed > (philo->table->time_to_die / 1000))
		return (TRUE);
	else
		return (FALSE);
}

bool	is_simulation_finished(t_table *table)
{
	return (get_bool(&table->mutex_table, &table->end_simulation));
}

void	*set_simulation_finished(void *arg)
{
	t_table			*table;
	int				i;

	table = (t_table *)arg;
	while (wait_simulation_start(&table->mutex_table,
			&table->nbr_philo_ready, table->nbr_of_philo) == FALSE
		|| table->start_simulation == 0)
		ft_usleep(200);
	while (is_simulation_finished(table) == FALSE)
	{
		i = 0;
		if (table->meal_to_finish > 0
			&& table->nbr_of_philo == table->philo_full)
			set_bool(&table->mutex_table, &table->end_simulation, TRUE);
		while (i < table->nbr_of_philo
			&& is_simulation_finished(table) == FALSE)
		{
			if (is_philo_dead(table->philo + i) == TRUE)
			{
				set_bool(&table->mutex_table, &table->end_simulation, TRUE);
				write_status(DIED, table->philo + i);
			}
			i++;
		}
		ft_usleep(200);
	}
	return (NULL);
}
