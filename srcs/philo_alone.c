/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_alone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:02:36 by adebert           #+#    #+#             */
/*   Updated: 2024/10/16 11:36:01 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*dinning_alone(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	wait_everyone(&philo->table->mutex_table, philo->table);
	set_long(&philo->mutex_philo, &philo->last_meal, get_time(MILLISECOND));
	incr_long(&philo->table->mutex_table, &philo->table->nbr_philo_ready);
	write_status(FORK, philo);
	while (is_simulation_finished(philo->table) == FALSE)
		ft_usleep(200);
	return (NULL);
}
