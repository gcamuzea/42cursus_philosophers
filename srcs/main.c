/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:15:07 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/19 14:00:36 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	if (args->number_of_meals < 0 || args->number_of_philos < 0 || args->time_to_die < 0
		|| args->time_to_eat < 0 || args->time_to_sleep < 0)
	{
		return (0);
	}
	return (1);
}

int	return_init_failure(const char *error_msg, t_parsed_args *args)
{
	if (args)
		free(args);
	printf("%s\n", error_msg);
	return (0);
}

void	free_philos(pthread_t **philos, t_philos_data **philos_d, int philos_count)
{
	int i;

	i = -1;
	if (philos)
	{
		while (++i < philos_count)
		{
			if (*(philos + i))
				free(*(philos + i));
		}
		free(philos);
	}
	i = -1;
	if (philos_d)
	{
		while (++i < philos_count)
		{
			if (*(philos_d + i))
				free(*(philos_d + i));
		}
		free(philos_d);
	}
}

void	*philo_thread(void *ptr)
{
	(void)ptr;
	// int philo_number;

	// philo_number = *(int *)ptr;
	printf("Philo succesfully created !\n");
	return (NULL);
}

t_philos_data	**create_philos_d(t_parsed_args *args)
{
	t_philos_data	**philos_d;

	philos_d = malloc(args->number_of_philos * sizeof(t_philos_data *));
	if (!philos_d)
		return (0);
	args->i = -1;
	while (++args->i < args->number_of_philos)
	{
		*(philos_d + args->i) = malloc(sizeof(t_philos_data));
		if (!*(philos_d + args->i))
		{
			while (--args->i)
				if (*(philos_d + args->i))
					free(*(philos_d + args->i));
			free(philos_d);
			return (0);
		}
	}
	args->i = -1;
	while (++args->i < args->number_of_philos)
	{
		pthread_mutex_init(&(*(philos_d + args->i))->fork, 0);
		(*(philos_d + args->i))->timers = args;
		(*(philos_d + args->i))->is_dead = 0;
		if (args->i == args->number_of_philos - 1)
			(*(philos_d + args->i))->neighbour = *(philos_d);
		else
			(*(philos_d + args->i))->neighbour = *(philos_d + args->i);
	}
	printf("philo data created\n");
	return (philos_d);
}

int main(int ac, char **av)
{
	t_parsed_args	*args;
	pthread_t		**philos_t;
	t_philos_data	**philos_d;

	args = check_args(ac, av);
	if (!args || !second_arg_check(args))
		return (return_init_failure("Error with args !", args));
	philos_t = malloc(args->number_of_philos * sizeof(pthread_t *));
	if (!philos_t)
		return (return_init_failure("Error whith malloc !", args));
	args->i = -1;
	while (++args->i < args->number_of_philos)
		*(philos_t + args->i) = malloc(sizeof(pthread_t));
	philos_d = create_philos_d(args);
	args->i = -1;
	while (++args->i < args->number_of_philos)
		pthread_create(philos_t[args->i], 0, philo_thread, philos_d[args->i]);
	free_philos(philos_t, philos_d, args->number_of_philos);
	free(args);
	printf("alles ok :)\n");
}