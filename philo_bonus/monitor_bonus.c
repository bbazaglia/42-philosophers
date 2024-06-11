/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:09:27 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/11 17:24:37 by bbazagli         ###   ########.fr       */
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
	sem_post(data->forks_sem);
	sem_unlink("forks");
	sem_unlink("print");
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	free(data->philo);
	return (status);
}

int	monitor(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	if (get_time_in_ms() > philo->last_meal + data->time_to_die)
	{
		safe_print(&philo[i], DEAD, DEBUG);
		data->end_simulation = true;
		return (exit_child(data, DEAD));
	}
	if (philo->meals_eaten == data->meals_required)
	{
		data->end_simulation = true;
		return (exit_child(data, FULL));
	}
	return (0);
}
