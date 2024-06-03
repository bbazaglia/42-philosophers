/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:49:01 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/03 16:22:41 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data **data, char **argv)
{
	int	i;

	*data = (t_data *)malloc(sizeof(t_data));
	(*data)->start_time = get_time_in_ms();
	(*data)->num_philosophers = atoi(argv[1]);
	(*data)->time_to_die = atoi(argv[2]);
	(*data)->time_to_eat = atoi(argv[3]);
	(*data)->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		(*data)->meals_required = ft_atol(argv[5]);
	else
		(*data)->meals_required = -1;
	(*data)->philosophers = (t_philo *)malloc(sizeof(t_philo)
			* (*data)->num_philosophers);
	(*data)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (*data)->num_philosophers);
	i = 0;
	while (i < (*data)->num_philosophers)
	{
		pthread_mutex_init(&((*data)->forks[i]), NULL);
		i++;
	}
	init_philos(*data);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].left_fork = &(data->forks[i]);
		data->philosophers[i].right_fork = &(data->forks[(i + 1)
				% data->num_philosophers]);
		data->philosophers[i].last_meal = 0;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].thread = (pthread_t *)malloc(sizeof(pthread_t));
		i++;
	}
}
