/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:15:07 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/21 18:12:19 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	philos_d = setup_philos_d(args);
	gettimeofday(&args->start_time, 0);
	pthread_mutex_init(&args->write_mutex, 0);
	args->i = -1;
	while (++args->i < args->number_of_philos)
		pthread_create(philos_t[args->i], 0, philo_thread, philos_d[args->i]);
	args->i = -1;
	while (++args->i < args->number_of_philos)
		pthread_join(*philos_t[args->i], 0);
	free_philos(philos_t, philos_d, args->number_of_philos);
	free(args);
	printf("alles ok :)\n");
}