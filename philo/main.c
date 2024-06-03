/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:52:17 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/03 16:42:40 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		error_message();
	args_validation(argc, argv);
	init_data(&data, argv);
	cleanup(data);
}

void	routine(void *arg)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)arg;
	if (philosophers->id % 2 == 0)
	{
		pthread_mutex_lock(philosophers->right_fork);
		pthread_mutex_lock(philosophers->left_fork);
	}
	else
	{
		pthread_mutex_lock(philosophers->left_fork);
		pthread_mutex_lock(philosophers->right_fork);
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		// if (pthread_create(&data->philosophers[i].thread, NULL, routine,
		//			&data->philosophers[i]) != 0)
		// 	exit(printf("error creating threads\n"));
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		// pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}