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

void	init_monitor_threads(t_data *data)
{
	pthread_create(&data->death_monitor, NULL, death_monitor, data);
	pthread_create(&data->fullness_monitor, NULL, fullness_monitor, data);
}

void	end_monitor_threads(t_data *data)
{
	pthread_join(data->death_monitor, NULL);
	pthread_join(data->fullness_monitor, NULL);
	while (waitpid(-1, NULL, 0) != -1)
		;
}

// if the simulation ended for one reason, post the semaphore for the other,
// so that the other thread can end the simulation
void	end_simulation(t_data *data, int status)
{
	int i;

	safe_set(data->end_simulation, &data->simulation_finished, 1);
	kill_child_proc(data);
	if (status == FULL)
		sem_post(data->death_sem);
	if (status == DEAD)
	{
		i = 0;
		while (i < data->num_philo)
		{
			sem_post(data->full_sem);
			i++;
		}
	}
}

void	*death_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->death_sem);
	if (!data->end_simulation)
		end_simulation(data, DEAD);
	return (NULL);
}

void	*fullness_monitor(void *arg)
{
	t_data	*data;
	int		full_count;

	data = (t_data *)arg;
	full_count = 0;
	while (!is_simulation_finished(data))
	{
		sem_wait(data->full_sem);
		full_count++;
		if (full_count == data->num_philo)
			break ;
	}
	end_simulation(data, FULL);
	return (NULL);
}
