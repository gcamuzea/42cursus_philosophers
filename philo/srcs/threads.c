/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:11:57 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/14 16:10:55 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Modes :
// 0 to take a fork
// 1 to eat
// 2 to sleep
// 3 to think
// 4 to die
void	philo_output(int mode, t_pdata *philo)
{
	pthread_mutex_t	*mutex;

	mutex = &philo->timers->write_mutex;
	pthread_mutex_lock(mutex);
	printf("philo %d ", philo->philo_n);
	if (mode == 0)
		printf("has taken a fork\n");
	else if (mode == 1)
		printf("is eating\n");
	else if (mode == 2)
		printf("is sleeping\n");
	else if (mode == 3)
		printf("is thinking\n");
	else if (mode == 4)
		printf("is dead\n");
	pthread_mutex_unlock(mutex);
}

void	eating(t_pdata *philo_d)
{
	pthread_mutex_lock(&philo_d->fork);
	philo_output(0, philo_d);
	pthread_mutex_lock(philo_d->right_fork);
	philo_output(1, philo_d);
	philo_d->meals_eaten++;
	usleep(philo_d->timers->time_to_eat * 1000);
	pthread_mutex_unlock(&philo_d->fork);
	pthread_mutex_unlock(philo_d->right_fork);
}

void	*philo_thread(void *ptr)
{
	t_pdata			*philo_d;
	struct timeval	tv;
	double			elapsed_time;

	philo_d = ptr;
	// usleep(100000);
	elapsed_time = (double)(tv.tv_usec - philo_d->timers->start_time.tv_usec) / 1000;
	// printf("Philo %d succesfully created after %fms!\n", philo_d->philo_n, elapsed_time);
	while (1)
	{
		//1-eat
		eating(philo_d);
		philo_output(2, philo_d);
		usleep(philo_d->timers->time_to_sleep * 1000);
		philo_output(3, philo_d);
		return 0;
	}
	return (0);
}
