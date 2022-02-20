/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:59:41 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/20 20:55:14 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	schlafmutze(long int t_us, t_data *data)
{
	struct timeval	tv;
	struct timeval	tv2;

	if (is_done(data))
		return ;
	gettimeofday(&tv, 0);
	gettimeofday(&tv2, 0);
	while (get_time_ms(tv, tv2) < t_us)
	{
		if (is_done(data))
			return ;
		usleep(2000);
		gettimeofday(&tv2, 0);
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

static int	is_number(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	atoi_w_return(char *str, int *nb_ptr)
{
	int				negative;
	long long int	number;

	if (ft_strlen(str) > 10)
		return (0);
	negative = 1;
	number = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = -1;
		str++;
	}
	if (is_number(*str))
		while (*str && is_number(*str))
			number = number * 10 + (*str++ - 48);
	else
		return (0);
	number *= negative;
	if (number > INT_MAX || number < INT_MIN || *str != 0)
		return (0);
	*nb_ptr = (int)number;
	return (1);
}
