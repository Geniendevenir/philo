/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:44:25 by allan             #+#    #+#             */
/*   Updated: 2024/10/15 19:24:22 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
	long	elapsed_seconds;
	long	elapsed_microseconds;

	elapsed_seconds = (end.tv_sec - start.tv_sec) * 1000000L;
	elapsed_microseconds = end.tv_usec - start.tv_usec;
	return (elapsed_seconds + elapsed_microseconds);
}

int	ft_usleep(long usec)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;
	long			rem;

	if (usec < 0)
		return (write(2, ERR_USEC, 31), 1);
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem <= 0)
			break ;
		if (rem > 1000)
			usleep(rem / 2);
	}
	return (0);
}

long	get_time(e_time_unit time_unit)
{
	struct timeval	timestamp;

	if (gettimeofday(&timestamp, NULL) == ERROR)
		return (error_msg(ERR_GET_TIME), -1);
	if (time_unit == SECOND)
		return (timestamp.tv_sec + (timestamp.tv_usec / 1000000L));
	else if (time_unit == MILLISECOND)
		return ((timestamp.tv_sec * 1000L) + (timestamp.tv_usec / 1000L));
	else if (time_unit == MICROSECOND)
		return ((timestamp.tv_sec * 1000000L) + timestamp.tv_usec);
	else
		return (error_msg(ERR_TIME_UNIT), -1);
}

void	wait_everyone(pthread_mutex_t *mutex, t_table *table)
{
	while (get_bool(mutex, &table->is_everyone_ready) == FALSE
		|| table->start_simulation == 0)
		ft_usleep(200);
}

long	print_time(long start)
{
	long			curr;
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	curr = (timestamp.tv_sec * 1000L) + (timestamp.tv_usec / 1000L);
	return (curr - start);
}
