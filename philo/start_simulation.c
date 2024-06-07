/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:20:25 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/07 15:17:39 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_threads_creation(t_data *data)
{
	while (!get_bool(&(data->data_mutex), &(data->all_threads_created)))
		;
}

static void	*single_routine(void *data)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)data;
	data = philo->data;
	set_long(&(philo->philo_mutex), &(philo->last_meal), data->start_time);
	safe_mutex(LOCK, &(philo->first_fork->fork_mutex));
	safe_print(philo, TOOK_FIRST_FORK, false);
	safe_mutex(UNLOCK, &(philo->first_fork->fork_mutex));
}

static void	*philosophers_routine(void *data)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)data;
	data = philo->data;
	set_long(&(philo->philo_mutex), &(philo->last_meal), data->start_time);
	while (!simulation_finished(data))
	{
		if (philo->full)
			break ;
		eat(philo);
		// rest(philo);
		// think(philo);
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms();
	if (data->num_philo == 1)
		safe_thread(CREATE, &(data->philos[0]->thread_id), NULL, \
		single_routine, &(data->philos[0]));
	else
	{
		while (i < data->num_philo)
		{
			safe_thread(CREATE, &(data->philos[i]->thread_id), NULL, \
			philosophers_routine, &(data->philos[i]));
			i++;
		}
	}
	set_bool(&(data->data_mutex), &(data->all_threads_created), true);
	i = 0;
	while (i < data->num_philo)
	{
		safe_thread(JOIN, &(data->philos[i].thread_id), NULL, NULL, NULL);
		i++;
	}
}
