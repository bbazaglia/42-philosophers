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
	long	end_eating_time;

	data = philo->data;
	take_forks(philo);
	safe_set(&philo->last_meal_sem, &philo->last_meal, get_time_in_ms());
	end_eating_time = safe_get(&philo->last_meal_sem, &philo->last_meal) + data->time_to_eat;
	safe_print(philo, EATING, DEBUG);
	while (get_time_in_ms() < end_eating_time)
	{
		if (is_simulation_finished(data))
			break ;
		usleep(PAUSE);
	}
	philo->meals_eaten++;
	return_forks(philo);
	if (philo->meals_eaten == data->meals_required)
		sem_post(data->full_sem);
}

void	rest(t_philo *philo)
{
	long	end_sleeping_time;
	t_data	*data;

	data = philo->data;
	safe_print(philo, SLEEPING, DEBUG);
	end_sleeping_time = get_time_in_ms() + data->time_to_sleep;
	while (get_time_in_ms() < end_sleeping_time)
		usleep(PAUSE);
}

void	think(t_philo *philo)
{
	long	end_thinking_time;
	t_data	*data;

	data = philo->data;
	safe_print(philo, THINKING, DEBUG);
	end_thinking_time = (data->time_to_die - get_time_in_ms() - philo->last_meal
			- data->time_to_eat) / 2;
	if (end_thinking_time < 0)
		return ;
	if (end_thinking_time > 500)
		end_thinking_time = 500;
	else
	{
		while (get_time_in_ms() < end_thinking_time)
			usleep(PAUSE);
	}
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	sem_wait(philo->data->forks_sem);
	safe_print(philo, TOOK_FIRST_FORK, DEBUG);
	safe_print(philo, TOOK_SECOND_FORK, DEBUG);
}

void	return_forks(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
}