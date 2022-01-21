/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:27:21 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/21 18:33:46 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_parsed_args	*check_args(int ac, char **av)
{
	t_parsed_args *args;
	
	if (ac < 5 || ac > 6)
		return (0);
	args = malloc(sizeof(t_parsed_args));
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

int	second_arg_check(t_parsed_args *args)
{
	if (args->number_of_meals < 0 || args->number_of_philos < 0
    	|| args->time_to_die < 0 || args->time_to_eat < 0
    	|| args->time_to_sleep < 0)
	{
		return (0);
	}
	return (1);
}

t_philos_data	**malloc_philos_d(int number_of_philos)
{
	t_philos_data	**philos_d;
	int				i;

	philos_d = malloc(number_of_philos * sizeof(t_philos_data *));
	if (!philos_d)
		return (0);
	i = -1;
	while (++i < number_of_philos)
	{
		*(philos_d + i) = malloc(sizeof(t_philos_data));
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

t_philos_data	**setup_philos_d(t_parsed_args *args)
{
	t_philos_data	**philos_d;
	int				i;

	philos_d = malloc_philos_d(args->number_of_philos);
	if (!philos_d)
		return (0);
	i = -1;
	while (++i < args->number_of_philos)
	{
		(*(philos_d + i))->philo_n = i + 1;
		pthread_mutex_init(&(*(philos_d + i))->fork, 0);
		(*(philos_d + i))->timers = args;
		if (i == args->number_of_philos - 1)
			(*(philos_d + i))->neighbour = *(philos_d);
		else
			(*(philos_d + i))->neighbour = *(philos_d + i);
	}
	return (philos_d);
}
