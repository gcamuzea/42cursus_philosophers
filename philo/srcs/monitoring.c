/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:31:06 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/14 15:37:47 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_for_dead(t_pdata **philos_d, int philos_nb)
{
	int				i;
	long int		last_meal_in_ms;
	struct timeval	current_time;

	i = -1;
	while (++i < philos_nb)
	{
		gettimeofday(&current_time, 0);
		last_meal_in_ms = current_time.tv_usec - philos_d[i]->last_meal_time.tv_usec / 1000;
		printf("checking philo number %d, current time is %ld, last meal is %ld\n", i, current_time.tv_usec, philos_d[i]->last_meal_time.tv_usec);
		printf("last meal is %ldms ago\n", last_meal_in_ms);
		if (last_meal_in_ms >= philos_d[i]->timers->time_to_die)
			return (0);
	}
	return (1);
}

void	monitoring(t)