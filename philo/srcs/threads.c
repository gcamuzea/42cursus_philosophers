/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:11:57 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/20 21:07:12 by gucamuze         ###   ########.fr       */
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

int	is_done(t_data *data)
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
		gettimeofday(&tv, 0);
		time_in_ms = get_time_ms(philo->timers->start_time, tv);
		pthread_mutex_lock(mutex);
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

void	eating(t_pdata *philo_d)
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
	schlafmutze(philo_d->timers->time_to_eat, philo_d->timers);
	pthread_mutex_unlock(&philo_d->fork);
	pthread_mutex_unlock(philo_d->right_fork);
	if (++philo_d->meals_eaten == philo_d->timers->number_of_meals)
	{
		pthread_mutex_lock(&philo_d->timers->meals_mutex);
		philo_d->timers->nb_of_full_meals++;
		pthread_mutex_unlock(&philo_d->timers->meals_mutex);
	}
}

void	*philo_thread(void *ptr)
{
	t_pdata			*philo_d;
	t_data			*timers;

	philo_d = ptr;
	timers = philo_d->timers;
	if (!(philo_d->philo_n % 2))
		schlafmutze(timers->time_to_eat / 10, timers);
	if (timers->number_of_philos == 1)
		philo_output(0, philo_d);
	while (timers->number_of_philos > 1
		&& !is_done(timers))
	{
		eating(philo_d);
		philo_output(2, philo_d);
		schlafmutze(timers->time_to_sleep, timers);
		philo_output(3, philo_d);
		if (timers->number_of_philos % 2)
			schlafmutze(timers->time_to_eat, timers);
	}
	return (0);
}
