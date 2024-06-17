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

bool	is_simulation_finished(t_data *data)
{
	if (data->simulation_finished)
		return (true);
	return (false);
}

void	single_routine(t_data *data, t_philo *philo)
{
	sem_wait(data->forks_sem);
	safe_print(philo, TOOK_FIRST_FORK, DEBUG);
	while (!is_simulation_finished(data))
		;
}

void	multiple_routine(t_data *data, t_philo *philo)
{
	while (!is_simulation_finished(data))
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

