/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:04:15 by allan             #+#    #+#             */
/*   Updated: 2024/10/15 19:24:23 by adebert          ###   ########.fr       */
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
