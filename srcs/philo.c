/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:05:54 by allan             #+#    #+#             */
/*   Updated: 2024/09/19 04:45:18 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	argument;

	if (argc < 5 || argc > 6)
		return (write(1, ERR_NBR_ARG, 54), 1);
	if (check_arg(argv) == ERROR)
		return (write(1, ERR_ARG, 116), 1);
	if (init_arg(argc, argv, &argument) == ERROR)
		return (write(1,ERR_ARG, 116), 1);
	print_arg(argument);
	return (0);
}