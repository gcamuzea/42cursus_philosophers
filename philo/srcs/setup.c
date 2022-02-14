/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:27:21 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/14 16:10:44 by gucamuze         ###   ########.fr       */
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
	args->number_of_meals = 0;
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
	if (args->number_of_meals < 0 || args->number_of_philos < 0
		|| args->time_to_die < 0 || args->time_to_eat < 0
		|| args->time_to_sleep < 0)
	{
		return (0);
	}
	pthread_mutex_init(&args->write_mutex, 0);
	return (1);
}

t_pdata	**malloc_philos_d(int number_of_philos)
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

t_pdata	**setup_philos_d(t_data *args)
{
	t_pdata	**philos_d;
	int		i;

	philos_d = malloc_philos_d(args->number_of_philos);
	if (!philos_d)
		return (0);
	i = -1;
	while (++i < args->number_of_philos)
	{
		(*(philos_d + i))->philo_n = i + 1;
		pthread_mutex_init(&philos_d[i]->fork, 0);
		(*(philos_d + i))->timers = args;
		gettimeofday(&(*(philos_d + i))->last_meal_time, 0);
		philos_d[i]->meals_eaten = 0;
		// printf("setting up philo %d, gtod is %ld\n", i, (*(philos_d + i))->last_meal_time.tv_usec);
	}
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
