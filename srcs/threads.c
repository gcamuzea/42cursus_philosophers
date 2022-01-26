/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:11:57 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/22 18:24:34 by gucamuze         ###   ########.fr       */
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
		printf("checking philo number %d, current time is %ld, last meal is %ld\n", i, current_time.tv_usec, philos_d[i]->last_meal_time.tv_usec);
		printf("last meal is %ldms ago\n", last_meal_in_ms);
		if (last_meal_in_ms >= philos_d[i]->timers->time_to_die)
			return (0);
	}
	return (1);
}

void	*philo_thread(void *ptr)
{
	t_philos_data	*philo_d;
	struct timeval	tv;
	double			elapsed_time;

	philo_d = ptr;
	gettimeofday(&tv, 0);
	usleep(100000);
	elapsed_time = (double)(tv.tv_usec - philo_d->timers->start_time.tv_usec) / 1000;
	printf("Philo %d succesfully created after %fms!\n", philo_d->philo_n, elapsed_time);
	while (1)
	{
		if (!check_for_dead(philo_d->philos, philo_d->timers->number_of_philos))
		{
			printf("a philo is dead ! philo %d exiting\n", philo_d->philo_n);
			return (0);
		}
		usleep(1);
	}
	return (0);
}
