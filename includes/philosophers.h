/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:12:14 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/19 13:47:00 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_parsed_args
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	int					i;
}						t_parsed_args;

typedef struct s_philos_data
{
	// fork
	pthread_mutex_t 		fork;
	// philo voisin
	struct s_philos_data	*neighbour;
	// args
	t_parsed_args			*timers;
	// ded?
	int						is_dead;
}							t_philos_data;

enum	e_pstate
{
							EATING,
							THINKING,
							SLEEPING
};

int				atoi_w_return(char *str, int *nb_ptr);

#endif