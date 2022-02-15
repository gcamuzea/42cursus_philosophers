/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:15:07 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/14 16:44:22 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philos(pthread_t **philos, t_pdata **philos_d, int philos_nb)
{
	int	i;

	i = -1;
	if (philos)
	{
		while (++i < philos_nb)
		{
			if (*(philos + i))
				free(*(philos + i));
		}
		free(philos);
	}
	i = -1;
	if (philos_d)
	{
		while (++i < philos_nb)
		{
			if (*(philos_d + i))
				free(*(philos_d + i));
		}
		free(philos_d);
	}
}

int	return_and_free(const char *error_msg, t_data *args,
	pthread_t **philos_t, t_pdata **philos_d)
{
	free_philos(philos_t, philos_d, args->number_of_philos);
	if (args)
		free(args);
	ft_puts(error_msg);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

void	ft_puts(const char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

int	main(int ac, char **av)
{
	t_data			*args;
	pthread_t		**philos_t;
	t_pdata			**philos_d;

	args = check_args(ac, av);
	if (!args || !second_arg_check(args))
		return (return_and_free("Error with args !", args, 0, 0));
	philos_t = malloc(args->number_of_philos * sizeof(pthread_t *));
	if (!philos_t)
		return (return_and_free("Error whith malloc !", args, 0, 0));
	args->i = -1;
	while (++args->i < args->number_of_philos)
		*(philos_t + args->i) = malloc(sizeof(pthread_t));
	philos_d = setup_philos_d(args);
	if (!philos_d)
		return (return_and_free("Error whith malloc !", args, philos_t, 0));
	gettimeofday(&args->start_time, 0);
	args->i = -1;
	while (++args->i < args->number_of_philos)
		pthread_create(philos_t[args->i], 0, philo_thread, philos_d[args->i]);
	usleep(100);
	args->i = -1;
	while (++args->i < args->number_of_philos)
		pthread_join(*philos_t[args->i], 0);
	return (return_and_free("end", args, philos_t, philos_d));
}
