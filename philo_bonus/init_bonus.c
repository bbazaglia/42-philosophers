/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:49:01 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 10:16:48 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	create_processes(t_data *data, int i)
{
	data->philo[i].pid = fork();
	if (data->philo[i].pid < 0)
		exit(printf("Error: fork\n"));
	if (data->philo[i].pid == 0)
	{
		if (data->num_philo == 1)
			single_routine(&(data->philo[i]));
		else
			multiple_routine(&data->philo[i]);
	}
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
		data->philo[i].full = false;
		data->philo[i].dead = false;
		data->philo[i].data = data;
		data->philo[i].last_meal = 0;
		create_processes(data, i);
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
	sem_unlink("forks");
	sem_unlink("print");
	data->print_sem = sem_open("print", O_CREAT, 0644, 1);
	data->forks_sem = sem_open("forks", O_CREAT, 0644, data->num_philo);
	data->end_simulation = false;
	data->start_time = get_time_in_ms();
	init_philos(data);
}

