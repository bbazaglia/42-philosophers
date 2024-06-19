/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:09:27 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 17:58:40 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (true)
	{
		if ((get_time_in_ms() > safe_get(philo->last_meal_sem,
					&philo->last_meal) + data->time_to_die))
		{
			safe_print(philo, DEAD, DEBUG);
			sem_post(data->death_sem);
			break ;
		}
	}
	return (NULL);
}

void init_monitor_threads(t_data *data)
{
	pthread_create(&data->death_monitor, NULL, death_monitor, data);
	pthread_create(&data->fullness_monitor, NULL, fullness_monitor, data);
}

void end_monitor_threads(t_data *data)
{
	pthread_join(data->death_monitor, NULL);
	pthread_join(data->fullness_monitor, NULL);
	while (waitpid(-1, NULL, 0) != -1)
		;
}

void	*death_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->death_sem);
	if (!is_simulation_finished(data))
		end_simulation(data, DEAD);
	return (NULL);
}

void	*fullness_monitor(void *arg)
{
	t_data	*data;
	int		full_count;

	data = (t_data *)arg;
	full_count = 0;
	while (true)
	{
		sem_wait(data->full_sem);
		full_count++;
		if (full_count == data->num_philo)
			break ;
	}
	if (!is_simulation_finished(data))
		end_simulation(data, FULL);
	return (NULL);
}
