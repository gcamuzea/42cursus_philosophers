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
	if (!atoi_w_return(av[1], args->number_of_philos)
		|| !atoi_w_return(av[2], args->time_to_die)
		|| !atoi_w_return(av[3], args->time_to_eat)
		|| !atoi_w_return(av[4], args->time_to_sleep))
	{
		free(args);
		return (0);
	}
	if (ac == 6)
	{
		if (!atoi_w_return(av[5], args->number_of_meals))
		{
			free(args);
			return (0);
		}
	}
	return (args);
}

int main(int ac, char **av)
{
	if (!check_args(ac, av))
	{
		printf("Error with args !\n");
		exit(0);
	}
	else
	{
		printf("alles ok :)\n");
	}
}