/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:49:09 by bbazagli          #+#    #+#             */
/*   Updated: 2024/05/31 18:06:17 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * int gettimeofday(struct timeval *tv, NULL);
 * - The first parameter is a pointer to a struct timeval containing two elements: seconds and microseconds.
 * - The second parameter corresponds to the timezone, but it's specified as NULL because it's obsolete.
 */

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	// Convert seconds to milliseconds: tv.tv_sec * 1000
	// Convert microseconds to milliseconds: tv.tv_usec / 1000
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
