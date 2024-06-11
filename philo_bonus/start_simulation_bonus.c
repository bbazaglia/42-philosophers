/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:20:25 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/11 17:21:33 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*single_routine(void *data_ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)data_ptr;
	data = philo->data;
	philo->last_meal = data->start_time;
	sem_wait(data->forks_sem);
	safe_print(philo, TOOK_FIRST_FORK, DEBUG);
	sem_post(data->forks_sem);
	return (NULL);
}

static void	*multiple_routine(void *data_ptr)
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
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms();
	if (data->num_philo == 1)
	{
		single_routine(data->philo);
		usleep(PAUSE);
	}
	else
	{
		while (i < data->num_philo)
		{
			data->philo[i].last_meal = data->start_time;
			data->philo[i].pid = fork();
			if (data->philo[i].pid == -1)
				exit(printf("Fork error\n"));
			if (data->philo[i].pid == 0)
				multiple_routine(&data->philo[i]);
			i++;
		}
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
		else if (WIFEXITED(status) && WEXITSTATUS(status) == FULL)
			all_full++;
		if (all_full == data->num_philo)
		{
			kill_all_children(data);
			break ;
		}
	}
}