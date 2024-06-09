/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:20:37 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/07 15:13:35 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	t_data	*data;
	long	end_eating_time;

	data = philo->data;
	take_forks(philo);
	set_long(&(philo->philo_mutex), &(philo->last_meal), get_time_in_ms());
	end_eating_time = get_long(&(philo->philo_mutex), &(philo->last_meal)) + data->time_to_eat;
	while (get_time_in_ms() < end_eating_time)
	{
		if (simulation_finished(data))
			break ;
		usleep(PAUSE);
	}
	philo->meals_eaten++;
	safe_print(philo, EATING, DEBUG);
	return_forks(philo);
	if (philo->meals_eaten == data->meals_required)
		set_bool(&(philo->philo_mutex), &(philo->full), true);
}

void	rest(t_philo *philo)
{
	long end_sleeping_time;
	t_data *data;

	data = philo->data;
	safe_print(philo, SLEEPING, DEBUG);
	end_sleeping_time = get_time_in_ms() + data->time_to_sleep;
	while (get_time_in_ms() < end_sleeping_time)
	{
		if (simulation_finished(data))
			break ;
	usleep(PAUSE);
	}
}

void	think(t_philo *philo)
{
	safe_print(philo, THINKING, DEBUG);
	usleep(PAUSE);
}