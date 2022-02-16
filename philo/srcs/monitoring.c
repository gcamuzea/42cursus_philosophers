/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:31:06 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/16 22:44:10 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int		check_for_dead(t_pdata **philos_d, int philos_nb)
// {
	
// }

int	monitoring(t_pdata **philos, t_data *data)
{
	int				f;
	int				i;
	struct timeval	tv;

	f = 1;
	while (f)
	{
		i = -1;
		gettimeofday(&tv, 0);
		while (++i < data->number_of_philos)
		{
			if (get_time_ms(tv, philos[i]->last_meal_time) > data->time_to_die)
			{
				f = 0;
				printf("philo %d is dead !!\n", i + 1);
				break ;
			}
		}
	}
	return (0);
}
