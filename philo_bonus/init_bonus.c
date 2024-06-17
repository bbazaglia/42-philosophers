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

static void	*monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!is_simulation_finished(data))
	{
		if ((get_time_in_ms() > safe_get(philo->last_meal_sem,
					&philo->last_meal) + data->time_to_die))
		{
			safe_print(philo, DEAD, DEBUG);
			sem_post(data->death_sem);
			break ;
		}
	}
	return (NULL);
}

static void	create_processes(t_data *data, int i)
{
	data->philo[i].pid = fork();
	if (data->philo[i].pid == 0)
	{
		if (data->num_philo == 1)
			single_routine(data, &data->philo[i]);
		else
			multiple_routine(data, &data->philo[i]);
	}
}

static void	create_semaphores(t_data *data)
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

static void	create_threads(t_philo *philo)
{
	pthread_t	philo_thread;

	pthread_create(&philo_thread, NULL, monitor, philo);
	pthread_detach(philo_thread);
}

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].data = data;
		create_processes(data, i);
		create_threads(&data->philo[i]);
		sem_unlink("last_meal");
		data->philo[i].last_meal_sem = sem_open("last_meal", O_CREAT, 0644, 1);
		sem_unlink("last_meal");
		i++;
	}
}

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
	create_semaphores(data);
	data->start_time = get_time_in_ms();
	data->simulation_finished = 0;
	init_philos(data);
}
