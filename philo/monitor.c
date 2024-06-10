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

bool simulation_finished(t_data *data)
{
	return (get_bool(&(data->data_mutex), &(data->end_simulation)));
}

void wait_threads_creation(t_data *data)
{
	while (!get_bool(&(data->data_mutex), &(data->all_threads_created)))
		;
}

void monitor(t_data *data)
{
	int i;
    bool all_full;
    t_philo *philos;

	i = 0;
	all_full = true;
	philos = data->philos;
    wait_threads_creation(data);
    while (i < data->num_philo)
    {
        if (get_time_in_ms() > get_long(&philos[i].philo_mutex, &philos[i].last_meal) + data->time_to_die)
        {
            safe_print(&philos[i], DEAD, DEBUG);
            set_bool(&data->data_mutex, &data->end_simulation, true);
            return ;
        }
        if (!get_bool(&philos[i].philo_mutex, &philos[i].full))
            all_full = false;
		i++;
    }
    if (all_full)
        set_bool(&data->data_mutex, &data->end_simulation, true);
}
