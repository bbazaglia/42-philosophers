/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:57:28 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/07 15:16:19 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(int status, t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (status == EATING)
		printf(B "%ld %d is eating" RST "\n", timestamp(data->start_time), \
		philo->id);
	else if (status == SLEEPING)
		printf(G "%ld %d is sleeping" RST "\n", timestamp(data->start_time), \
		philo->id);
	else if (status == THINKING)
		printf(Y "%ld %d is thinking" RST "\n", timestamp(data->start_time), \
		philo->id);
	else if (status == TOOK_FIRST_FORK || status == TOOK_SECOND_FORK)
		printf(W "%ld %d has taken a fork" RST "\n", \
		timestamp(data->start_time), philo->id);
	else if (status == DEAD)
		printf(RED "%ld %d died" RST "\n", timestamp(data->start_time), \
		philo->id);
}

void	write_debug_status(int status, t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (status == EATING)
		printf(B "%ld %d is eating for the [%ld] time" RST "\n", \
		timestamp(data->start_time), philo->id, philo->meals_eaten);
	else if (status == SLEEPING)
		printf(G "%ld %d is sleeping" RST "\n", timestamp(data->start_time), \
		philo->id);
	else if (status == THINKING)
		printf(Y "%ld %d is thinking" RST "\n", timestamp(data->start_time), \
		philo->id);
	else if (status == TOOK_FIRST_FORK)
		printf(W "%ld %d has taken first fork" RST "\n", \
		timestamp(data->start_time), philo->id);
	else if (status == TOOK_SECOND_FORK)
		printf(W "%ld %d has taken second fork" RST "\n", \
		timestamp(data->start_time), philo->id);
	else if (status == DEAD)
		printf(RED "%ld %d died" RST "\n", timestamp(data->start_time), \
		philo->id);
}
