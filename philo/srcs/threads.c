/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:11:57 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/16 22:31:52 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time_ms(struct timeval tv1, struct timeval tv2)
{
	if (tv2.tv_sec > tv1.tv_sec)
		return (((1000000 * (tv2.tv_sec - tv1.tv_sec))
				- tv1.tv_usec + tv2.tv_usec) / 1000);
	return ((tv2.tv_usec - tv1.tv_usec) / 1000);
}

// Modes :
// 0 to take a fork
// 1 to eat
// 2 to sleep
// 3 to think
// 4 to die
void	philo_output(int mode, t_pdata *philo)
{
	pthread_mutex_t	*mutex;
	struct timeval	tv;
	int				time_in_ms;

	mutex = &philo->timers->write_mutex;
	pthread_mutex_lock(mutex);
	gettimeofday(&tv, 0);
	time_in_ms = get_time_ms(philo->timers->start_time, tv);
	printf("%d\tphilo %d ", time_in_ms, philo->philo_n);
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
	struct timeval	tv;
	struct timeval	tv2;

	pthread_mutex_lock(&philo_d->fork);
	philo_output(0, philo_d);
	pthread_mutex_lock(philo_d->right_fork);
	gettimeofday(&tv, 0);
	philo_output(1, philo_d);
	usleep(philo_d->timers->time_to_eat * 1000);
	pthread_mutex_unlock(&philo_d->fork);
	pthread_mutex_unlock(philo_d->right_fork);
	pthread_mutex_lock(&philo_d->lml_mutex);
	gettimeofday(&philo_d->last_meal_time, 0);
	philo_d->meals_eaten++;
	pthread_mutex_unlock(&philo_d->lml_mutex);
	gettimeofday(&tv2, 0);
	// printf("philo %d time elapsed : %ums\n", philo_d->philo_n, get_time_ms(tv, tv2));
}

void	*philo_thread(void *ptr)
{
	t_pdata			*philo_d;
	struct timeval	tv;
	struct timeval	tv2;

	philo_d = ptr;
	while (philo_d->state != DEAD)
	{
		gettimeofday(&tv, 0);
		//1-eat
		eating(philo_d);
		gettimeofday(&tv2, 0);
		// printf("thread %d time elapsed = %dms\n", philo_d->philo_n, get_time_ms(tv, tv2));
		philo_output(2, philo_d);
		usleep(philo_d->timers->time_to_sleep * 1000);
		philo_output(3, philo_d);
		// printf("%d meals eaten by thread %d\n", philo_d->meals_eaten, philo_d->philo_n);
		// if (philo_d->meals_eaten > 0)
		// 	return 0;
	}
	return (0);
}
