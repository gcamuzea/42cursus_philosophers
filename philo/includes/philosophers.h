/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:12:14 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/14 16:43:43 by gucamuze         ###   ########.fr       */
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

enum	e_pstate
{
	EATING,
	THINKING,
	SLEEPING
};

typedef struct s_args
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	int					i;
	struct timeval		start_time;
	pthread_mutex_t		write_mutex;
}						t_data;

typedef struct s_philos_data
{
	int						philo_n;
	pthread_mutex_t			fork;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			lml_mutex;
	t_data					*timers;
	struct timeval			last_meal_time;
	int						meals_eaten;
}							t_pdata;

typedef struct s_monitoring
{
	pthread_mutex_t		death_mutex;
	int					dead;
}	t_monitoring;

// Setup
t_data						*check_args(int ac, char **av);
int							second_arg_check(t_data *args);
t_pdata						**malloc_philos_d(int number_of_philos);
t_pdata						**setup_philos_d(t_data *args);

int							atoi_w_return(char *str, int *nb_ptr);

void						*philo_thread(void *ptr);

void						ft_puts(const char *str);

#endif