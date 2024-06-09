/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:09:27 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/07 15:09:36 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_finished(t_data *data)
{
	return (get_bool(&(data->data_mutex), &(data->end_simulation)));
}

static bool	all_philosophers_full(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		if (!get_bool(&(data->philos[i].philo_mutex), &(data->philos[i].full)))
			return (false);
		i++;
	}
	return (true);
}

void *monitor(void *data_ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_ptr;
	while (!simulation_finished(data))
	{
		i = 0;
		while (i < data->num_philo)
		{
			if ((get_time_in_ms() - get_long(&(data->philos[i].philo_mutex),
					&(data->philos[i].last_meal))) > data->time_to_die)
			{
				safe_print(&(data->philos[i]), DEAD, DEBUG);
				set_bool(&(data->data_mutex), &(data->end_simulation), true);
				break ;
			}
			i++;
		}
		if (all_philosophers_full(data))
			set_bool(&(data->data_mutex), &(data->end_simulation), true);
	}
	return (NULL);
}

