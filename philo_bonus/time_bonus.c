/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:49:09 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/11 11:41:55 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*  gettimeofday() returns the current time in seconds and microseconds.
 * 	Convert seconds to milliseconds: tv.tv_sec * 1000
 *  Convert microseconds to milliseconds: tv.tv_usec / 1000             */

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	timestamp(long start_time)
{
	return (get_time_in_ms() - start_time);
}
