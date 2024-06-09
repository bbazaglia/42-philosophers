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

/* Accessing Struct Instances vs. Accessing Members of a Struct Through a Pointer

- Accessing Struct Instances:
data->philos[i] is a struct instance because philos is an array of t_philo structs.
Use the dot operator to access members: data->philos[i].member.

- Accessing Members of a Struct Through a Pointer:
philo is a pointer to a t_philo struct (t_philo *philo)
Use the arrow operator to access members: philo->member.
*/


static void	wait_threads_creation(t_data *data)
{
	while (!get_bool(&(data->data_mutex), &(data->all_threads_created)))
		;
}

static void *single_routine(void *data_ptr)
{
    t_philo *philo; 
    t_data *data; 

    philo = (t_philo *)data_ptr; // cast the void * to t_philo *
    data = philo->data; // access the data field in the struct t_philo
    set_long(&(philo->philo_mutex), &(philo->last_meal), data->start_time);
    safe_mutex(LOCK, &(philo->first_fork->fork_mutex));
    safe_print(philo, TOOK_FIRST_FORK, false);
    safe_mutex(UNLOCK, &(philo->first_fork->fork_mutex));
	return (NULL);
}

static void	*multiple_routine(void *data_ptr)
{
	t_philo	*philo; 
	t_data	*data; 

	philo = (t_philo *)data_ptr;
	data = philo->data;
	wait_threads_creation(data);
	set_long(&(philo->philo_mutex), &(philo->last_meal), data->start_time);
	while (!simulation_finished(data))
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
	return (NULL);
}

void start_simulation(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_time_in_ms();
    if (data->num_philo == 1)
        safe_thread(CREATE, &(data->philos[0].thread_id), single_routine, &(data->philos[0]));
    else
    {
        while (i < data->num_philo)
        {
            safe_thread(CREATE, &(data->philos[i].thread_id), multiple_routine, &(data->philos[i]));
            i++;
        }
    }
    set_bool(&(data->data_mutex), &(data->all_threads_created), true);
    i = 0;
    while (i < data->num_philo)
    {
        safe_thread(JOIN, &(data->philos[i].thread_id), NULL, NULL);
        i++;
    }
}

