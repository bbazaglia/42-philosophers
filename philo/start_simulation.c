/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:20:25 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/11 10:27:53 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*single_routine(void *data_ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)data_ptr;
	data = philo->data;
	set_long(&(philo->philo_mutex), &(philo->last_meal), data->start_time);
	safe_mutex(LOCK, &(philo->first_fork->fork_mutex));
	safe_print(philo, TOOK_FIRST_FORK, DEBUG);
	safe_mutex(UNLOCK, &(philo->first_fork->fork_mutex));
	return (NULL);
}

static void	*multiple_routine(void *data_ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)data_ptr;
	data = philo->data;
	while (!simulation_finished(data))
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms();
	if (data->num_philo == 1)
	{
		safe_thread(CREATE, &(data->philos[0].thread_id), single_routine,
			&(data->philos[0]));
		usleep(PAUSE);
	}
	else
	{
		while (i < data->num_philo)
		{
			set_long(&(data->philos[i].philo_mutex),
				&(data->philos[i].last_meal),
				data->start_time);
			safe_thread(CREATE, &(data->philos[i].thread_id), multiple_routine,
				&(data->philos[i]));
			i++;
		}
	}
	set_bool(&(data->data_mutex), &(data->all_threads_created), true);
}

void	wait_threads_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		safe_thread(JOIN, &(data->philos[i].thread_id), NULL, NULL);
		i++;
	}
}
