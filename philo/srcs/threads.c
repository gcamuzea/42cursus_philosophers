/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:11:57 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/17 03:25:18 by gucamuze         ###   ########.fr       */
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

static int	check_for_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
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

	pthread_mutex_lock(&philo->timers->death_mutex);
	if (!philo->timers->dead)
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
	pthread_mutex_unlock(&philo->timers->death_mutex);
}

static void	eating(t_pdata *philo_d)
{
	if (philo_d->philo_n % 2)
		pthread_mutex_lock(&philo_d->fork);
	else
		pthread_mutex_lock(philo_d->right_fork);
	if (philo_d->philo_n % 2)
		pthread_mutex_lock(philo_d->right_fork);
	else
		pthread_mutex_lock(&philo_d->fork);
	philo_output(0, philo_d);
	philo_output(1, philo_d);
	usleep(philo_d->timers->time_to_eat * 1000);
	pthread_mutex_unlock(&philo_d->fork);
	pthread_mutex_unlock(philo_d->right_fork);
	pthread_mutex_lock(&philo_d->lml_mutex);
	gettimeofday(&philo_d->last_meal_time, 0);
	pthread_mutex_unlock(&philo_d->lml_mutex);
	pthread_mutex_lock(&philo_d->meals_mutex);
	philo_d->meals_eaten++;
	pthread_mutex_unlock(&philo_d->meals_mutex);
}

void	*philo_thread(void *ptr)
{
	t_pdata			*philo_d;

	philo_d = ptr;
	if ((philo_d->philo_n + 1) % 2)
		usleep(800);
	else
		usleep(200);
	while (philo_d->timers->number_of_philos > 1
		&& !check_for_dead(philo_d->timers))
	{
		eating(philo_d);
		philo_output(2, philo_d);
		usleep(philo_d->timers->time_to_sleep * 1000);
		philo_output(3, philo_d);
	}
	return (0);
}
