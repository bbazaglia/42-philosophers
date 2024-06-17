/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:20:25 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 10:57:06 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	single_routine(void *data_ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)data_ptr;
	data = philo->data;
	philo->last_meal = 0;
	sem_wait(data->forks_sem);
	safe_print(philo, TOOK_FIRST_FORK, DEBUG);
	sem_post(data->forks_sem);
	if (!simulation_finished(data))
		monitor(data);
}

void	multiple_routine(void *data_ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)data_ptr;
	data = philo->data;
	while (!simulation_finished(data))
	{
		eat(philo);
		rest(philo);
		think(philo);
		monitor(data);
	}
}

static void	kill_all_children(t_data *data)
{
	int	i;

	i = 0;
	printf("kill_all_children\n");
	while (i < data->num_philo)
	{

		if (kill(data->philo[i].pid, SIGKILL) == -1)
			exit(printf("Error: kill\n"));
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
	printf("father_process\n");
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