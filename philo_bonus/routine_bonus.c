/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:20:25 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 17:59:05 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	single_routine(t_data *data, t_philo *philo)
{
	sem_unlink("last_meal");
	philo->last_meal_sem = sem_open("last_meal", O_CREAT, 0644, 1);
	sem_unlink("last_meal");
	create_philo_thread(philo);
	sem_wait(data->forks_sem);
	safe_print(philo, TOOK_FIRST_FORK, DEBUG);
	while (true)
		;
}

void	multiple_routine(t_philo *philo)
{
	sem_unlink("last_meal");
	philo->last_meal_sem = sem_open("last_meal", O_CREAT, 0644, 1);
	sem_unlink("last_meal");
	create_philo_thread(philo);
	while (true)
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
}

void	kill_child_proc(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		kill(data->philo[i].pid, SIGKILL);
		i++;
	}
}

// if the simulation ended for one reason, post the semaphore for the other,
// so that the other thread can end the simulation
void	end_simulation(t_data *data, int status)
{
	int i;

	safe_set(data->end_simulation, &data->simulation_finished, 1);
	kill_child_proc(data);
	if (status == FULL)
		sem_post(data->death_sem);
	if (status == DEAD)
	{
		i = 0;
		while (i < data->num_philo)
		{
			sem_post(data->full_sem);
			i++;
		}
	}
}