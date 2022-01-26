/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:12:14 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/26 11:30:30 by gucamuze         ###   ########.fr       */
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
# include <stdarg.h>

typedef struct s_parsed_args
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	int					i;
	struct timeval		start_time;
	pthread_mutex_t		write_mutex;
}						t_parsed_args;

typedef struct s_philos_data
{
	int						philo_n;
	pthread_mutex_t 		fork;
	struct s_philos_data	*neighbour;
	t_parsed_args			*timers;
	struct timeval			last_meal_time;
}							t_philos_data;

enum	e_pstate
{
							EATING,
							THINKING,
							SLEEPING
};

t_parsed_args				*check_args(int ac, char **av);
int							second_arg_check(t_parsed_args *args);
t_philos_data				**malloc_philos_d(int number_of_philos);
t_philos_data				**setup_philos_d(t_parsed_args *args);

int							atoi_w_return(char *str, int *nb_ptr);

void						*philo_thread(void *ptr);

char						*cat_str(char *str, int nb_of_strs, ...);

#endif