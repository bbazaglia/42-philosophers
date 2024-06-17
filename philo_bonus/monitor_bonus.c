/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:09:27 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 14:54:34 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	simulation_finished(t_data *data)
{
	if (data->end_simulation)
		return (true);
	return (false);
}

int	exit_child(t_data *data, int status)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	free(data->philo);
	exit(status);
}

void	monitor(t_philo *philo)
{
	if (get_time_in_ms() > philo->last_meal + philo->data->time_to_die)
	{
		philo->data->end_simulation = true;
		exit_child(philo->data, DEAD);
	}
	if (philo->meals_eaten == philo->data->meals_required)
	{
		philo->data->end_simulation = true;
		exit_child(philo->data, FULL);
	}
}
