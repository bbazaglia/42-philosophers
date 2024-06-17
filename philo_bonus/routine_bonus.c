/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:20:25 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 13:48:53 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	single_routine(t_data *data, t_philo *philo)
{
	philo->last_meal = data->start_time;
	sem_wait(data->forks_sem);
	safe_print(philo, TOOK_FIRST_FORK, DEBUG);
	sem_post(data->forks_sem);
	while (!simulation_finished(data))
		monitor(philo);
}

void	multiple_routine(t_data *data, t_philo *philo)
{
	while (!simulation_finished(data))
	{
		eat(philo);
		rest(philo);
		think(philo);
		monitor(philo);
	}
}

static void	kill_all_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		kill(data->philo[i].pid, SIGKILL);
		i++;
	}
}

void	father_process(t_data *data)
{
	int i;
	int status;
	int all_full;

	i = 0;
	all_full = 0;
	status = EXIT_SUCCESS;
	while (i < data->num_philo)
	{
		// waits for any child process to change state and stores its status information in the variable status
		waitpid(0, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			kill_all_children(data);
			break ;
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == DEAD)
		{
			safe_print(data->philo, DEAD, DEBUG);
			kill_all_children(data);
			break ;
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == FULL)
			all_full++;
		if (all_full == data->num_philo)
		{
			kill_all_children(data);
			break ;
		}
	}
}