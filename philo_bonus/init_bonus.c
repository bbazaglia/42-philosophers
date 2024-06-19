/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:49:01 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 17:58:17 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_data(t_data *data, char **argv)
{
	data->num_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->meals_required = ft_atol(argv[5]);
	else
		data->meals_required = -1;
	data->simulation_finished = 0;
	create_semaphores(data);
	data->start_time = get_time_in_ms();
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].data = data;
		data->philo[i].last_meal = data->start_time;
		create_processes(data, i);
		i++;
	}
}

/* Each philosopher is represented by a separate process and they do not share memory directly.
Communicatition is done via signals (kill()) and semaphores (sem_t). */
void	create_processes(t_data *data, int i)
{
	data->philo[i].pid = fork();
	if (data->philo[i].pid == 0)
	{
		if (data->num_philo == 1)
			single_routine(data, &data->philo[i]);
		else
			multiple_routine(&data->philo[i]);
	}
}

// Threads are used for background tasks that require shared memory and synchronization (monitoring).
void	create_philo_thread(t_philo *philo)
{
	pthread_t	philo_thread;

	pthread_create(&philo_thread, NULL, monitor, philo);
	pthread_detach(philo_thread);
}

void	create_semaphores(t_data *data)
{
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("death");
	sem_unlink("full");
	sem_unlink("end");
	data->print_sem = sem_open("print", O_CREAT, 0644, 1);
	data->forks_sem = sem_open("forks", O_CREAT, 0644, data->num_philo);
	data->death_sem = sem_open("death", O_CREAT, 0644, 0);
	data->full_sem = sem_open("full", O_CREAT, 0644, 0);
	data->end_simulation = sem_open("end", O_CREAT, 0644, 1);
}
