/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:55:33 by adebert           #+#    #+#             */
/*   Updated: 2024/10/15 19:17:50 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	wait_simulation_start(pthread_mutex_t *mutex, long *threads, long nbr_philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == nbr_philo)
		ret = true;
	return (ret);
}

void	desynchronize_philo(t_philo *philo)
{
	if (philo->table->nbr_of_philo % 2 == 0)
	{
		if (philo->place % 2 == 0)
			ft_usleep(30);
	}
	else if (philo->table->nbr_of_philo % 2 != 0)
	{
		if (philo->place % 2)
			ft_think(philo, 0);
	}
	return ;
}
