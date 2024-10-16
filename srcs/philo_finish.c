/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:57:26 by adebert           #+#    #+#             */
/*   Updated: 2024/10/16 12:34:25 by adebert          ###   ########.fr       */
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
	t_table			*t;
	int				i;

	t = (t_table *)arg;
	while (wait_simulation_start(&t->mutex_table,
			&t->nbr_philo_ready, t->nbr_of_philo) == FALSE
		|| t->start_simulation == 0)
		ft_usleep(200);
	while (is_simulation_finished(t) == FALSE)
	{
		i = 0;
		if (t->meal_to_finish > 0 && t->nbr_of_philo == t->philo_full)
			set_bool(&t->mutex_table, &t->end_simulation, TRUE);
		while (i < t->nbr_of_philo && is_simulation_finished(t) == FALSE)
		{
			if (is_philo_dead(t->philo + i) == TRUE)
			{
				set_bool(&t->mutex_table, &t->end_simulation, TRUE);
				write_status(DIED, t->philo + i);
			}
			i++;
		}
		ft_usleep(200);
	}
	return (NULL);
}
