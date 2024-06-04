/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:20:25 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/04 17:15:18 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_threads_creation(t_data *data)
{
	while (!get_bool(&(data->data_mutex), &(data->all_threads_created)))
		;
}

static void	*philo_routine(void *data)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)data;
	data = philo->data;
	wait_threads_creation(data);
	set_long(&(philo->philo_mutex), &(philo->last_meal), data->start_time);
	while (!simulation_finished(data))
	{
		// eat(philo);
		// rest(philo);
		// think(philo);
	}
}

void	start_simulation(t_data *data)
{
	int		i;
	t_philo	*philo;

	if (data->num_philo == 1)
		// start_single_simulation(data);
		i = 0;
	while (i < data->num_philo)
	{
		philo = &(data->philo[i]);
		safe_thread(CREATE, &(philo->thread_id), NULL, philo_routine, philo);
		i++;
	}
	data->start_time = get_time_in_ms();
	set_bool(&(data->data_mutex), &(data->all_threads_created), true);
	i = 0;
	while (i < data->num_philo)
	{
		safe_thread(JOIN, &(data->philo[i].thread_id), NULL, NULL, NULL);
		i++;
	}
}
