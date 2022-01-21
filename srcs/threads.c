/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:11:57 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/21 18:34:25 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_for_dead(t_philos_data **philos_d, int philos_nb)
{
	int				i;
	long int		last_meal_in_ms;
	struct timeval	current_time;

	i = -1;
	while (++i < philos_nb)
	{
		gettimeofday(&current_time, 0);
		last_meal_in_ms = current_time.tv_usec - philos_d[i]->last_meal_time.tv_usec / 1000;
		if (last_meal_in_ms >= philos_d[i]->timers->time_to_die)
		{
			printf("Philosopher %d is now DED\n", philos_d[i]->philo_n);
			return (0);
		}
	}
	return (1);
}

void	*philo_thread(void *ptr)
{
	t_philos_data	*philo_d;
	struct timeval	tv;
	suseconds_t		elapsed_time;

	philo_d = ptr;
	usleep(10000);
	gettimeofday(&tv, 0);
	elapsed_time = (tv.tv_usec - philo_d->timers->start_time.tv_usec) / 1000;
	printf("Philo %d succesfully created after %ldms!\n", philo_d->philo_n, elapsed_time);
	return (0);
}
