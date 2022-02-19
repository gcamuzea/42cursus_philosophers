/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:11:57 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/19 19:31:32 by gucamuze         ###   ########.fr       */
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

static int	is_done(t_data *data)
{
	pthread_mutex_lock(&data->done_mutex);
	if (data->done)
	{
		pthread_mutex_unlock(&data->done_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->done_mutex);
	return (0);
}

// Modes : 0 to take a fork, 1 to eat, 2 to sleep,
// 3 to think, 4 to die
void	philo_output(int mode, t_pdata *philo)
{
	pthread_mutex_t	*mutex;
	struct timeval	tv;
	int				time_in_ms;

	pthread_mutex_lock(&philo->timers->done_mutex);
	if (!philo->timers->done)
	{
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
	pthread_mutex_unlock(&philo->timers->done_mutex);
}

static void	eating(t_pdata *philo_d)
{
	if (philo_d->philo_n % 2)
		pthread_mutex_lock(&philo_d->fork);
	else
		pthread_mutex_lock(philo_d->right_fork);
	philo_output(0, philo_d);
	if (philo_d->philo_n % 2)
		pthread_mutex_lock(philo_d->right_fork);
	else
		pthread_mutex_lock(&philo_d->fork);
	philo_output(0, philo_d);
	philo_output(1, philo_d);
	pthread_mutex_lock(&philo_d->lml_mutex);
	gettimeofday(&philo_d->last_meal_time, 0);
	pthread_mutex_unlock(&philo_d->lml_mutex);
	if (++philo_d->meals_eaten == philo_d->timers->number_of_meals)
	{
		pthread_mutex_lock(&philo_d->timers->meals_mutex);
		philo_d->timers->nb_of_full_meals++;
		pthread_mutex_unlock(&philo_d->timers->meals_mutex);
	}
	usleep(philo_d->timers->time_to_eat * 1000);
	pthread_mutex_unlock(&philo_d->fork);
	pthread_mutex_unlock(philo_d->right_fork);
}

void	*philo_thread(void *ptr)
{
	t_pdata			*philo_d;

	philo_d = ptr;
	if ((philo_d->philo_n + 1) % 2)
		usleep(philo_d->philo_n * 5 + 200);
	else
		usleep(philo_d->philo_n * 5);
	while (philo_d->timers->number_of_philos > 1
		&& !is_done(philo_d->timers))
	{
		eating(philo_d);
		philo_output(2, philo_d);
		usleep(philo_d->timers->time_to_sleep * 1000);
		philo_output(3, philo_d);
		if (philo_d->timers->number_of_philos % 2)
			usleep(50);
		else
			usleep(100);
	}
	return (0);
}
