/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:20:37 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 17:52:01 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (is_simulation_finished(data))
		return ;
	take_forks(philo);
	safe_set(philo->last_meal_sem, &philo->last_meal, get_time_in_ms());
	safe_print(philo, EATING, DEBUG);
	philo->meals_eaten++;
	usleep(data->time_to_eat * 1000);
	return_forks(philo);
	if (philo->meals_eaten == data->meals_required)
		sem_post(data->full_sem);
}

void	rest(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (is_simulation_finished(data))
		return ;
	safe_print(philo, SLEEPING, DEBUG);
	usleep(data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	long	end_thinking_time;
	t_data	*data;

	data = philo->data;
	if (is_simulation_finished(data))
		return ;
	safe_print(philo, THINKING, DEBUG);
	end_thinking_time = (data->time_to_die - get_time_in_ms() - philo->last_meal
			- data->time_to_eat) / 2;
	if (end_thinking_time < 0)
		return ;
	if (end_thinking_time > 500)
		end_thinking_time = 500;
	else
		usleep(end_thinking_time * 1000);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	safe_print(philo, TOOK_FIRST_FORK, DEBUG);
	sem_wait(philo->data->forks_sem);
	safe_print(philo, TOOK_SECOND_FORK, DEBUG);
}

void	return_forks(t_philo *philo)
{
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
}