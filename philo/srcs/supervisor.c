/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:31:06 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/17 05:22:31 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_stop_flag(t_data *data)
{
	pthread_mutex_lock(&data->done_mutex);
	data->done = 1;
	pthread_mutex_unlock(&data->done_mutex);
}

static int	check_death_timer(t_pdata *philo, t_data *data,
	struct timeval tv)
{
	pthread_mutex_lock(&philo->lml_mutex);
	if (get_time_ms(philo->last_meal_time, tv) > data->time_to_die)
	{
		philo_output(4, philo);
		set_stop_flag(data);
		pthread_mutex_unlock(&philo->lml_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->lml_mutex);
	return (1);
}

void	supervisor(t_pdata **philos, t_data *data)
{
	int				f;
	int				i;
	struct timeval	tv;

	f = 1;
	while (f)
	{
		i = -1;
		while (f && ++i < data->number_of_philos)
		{
			gettimeofday(&tv, 0);
			f = check_death_timer(philos[i], data, tv);
			pthread_mutex_lock(&data->meals_mutex);
			if (data->nb_of_full_meals == data->number_of_philos)
			{
				set_stop_flag(data);
				f = 0;
			}
			pthread_mutex_unlock(&data->meals_mutex);
		}
		usleep(50);
	}
}
