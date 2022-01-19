/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:59:41 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/19 13:59:59 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <ctype.h>

int	is_number(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	atoi_w_return(char *str, int *nb_ptr)
{
	int				negative;
	long long int	number;

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
