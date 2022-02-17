/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:27:21 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/17 04:14:21 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*check_args(int ac, char **av)
{
	t_data	*args;

	if (ac < 5 || ac > 6)
		return (0);
	args = malloc(sizeof(t_data));
	if (!args)
		return (0);
	args->number_of_meals = INT_MAX;
	if (!atoi_w_return(av[1], &args->number_of_philos)
		|| !atoi_w_return(av[2], &args->time_to_die)
		|| !atoi_w_return(av[3], &args->time_to_eat)
		|| !atoi_w_return(av[4], &args->time_to_sleep))
	{
		free(args);
		return (0);
	}
	if (ac == 6)
	{
		if (!atoi_w_return(av[5], &args->number_of_meals))
		{
			free(args);
			return (0);
		}
	}
	return (args);
}

int	second_arg_check(t_data *args)
{
	if (args->number_of_meals < 0 || args->number_of_philos <= 0
		|| args->time_to_die <= 0 || args->time_to_eat <= 0
		|| args->time_to_sleep <= 0)
	{
		return (0);
	}
	pthread_mutex_init(&args->write_mutex, 0);
	pthread_mutex_init(&args->done_mutex, 0);
	args->done = 0;
	return (1);
}

static t_pdata	**malloc_philos_d(int number_of_philos)
{
	t_pdata	**philos_d;
	int		i;

	philos_d = malloc(number_of_philos * sizeof(t_pdata *));
	if (!philos_d)
		return (0);
	i = -1;
	while (++i < number_of_philos)
	{
		*(philos_d + i) = malloc(sizeof(t_pdata));
		if (!*(philos_d + i))
		{
			while (--i)
				if (*(philos_d + i))
					free(*(philos_d + i));
			free(philos_d);
			return (0);
		}
	}
	return (philos_d);
}

static void	initialize_philo(t_pdata *philo, t_data *args, int philo_n)
{
	philo->philo_n = philo_n;
	pthread_mutex_init(&philo->fork, 0);
	pthread_mutex_init(&philo->lml_mutex, 0);
	pthread_mutex_init(&philo->meals_mutex, 0);
	philo->timers = args;
	gettimeofday(&philo->last_meal_time, 0);
	philo->meals_eaten = 0;
}

t_pdata	**setup_philos_d(t_data *args)
{
	t_pdata	**philos_d;
	int		i;

	philos_d = malloc_philos_d(args->number_of_philos);
	if (!philos_d)
		return (0);
	i = -1;
	while (++i < args->number_of_philos)
		initialize_philo(philos_d[i], args, i + 1);
	i = -1;
	while (++i < args->number_of_philos)
	{
		if (i != args->number_of_philos - 1)
			philos_d[i]->right_fork = &philos_d[i + 1]->fork;
		else
			philos_d[i]->right_fork = &philos_d[0]->fork;
	}
	return (philos_d);
}
