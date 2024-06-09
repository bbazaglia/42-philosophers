/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:49:01 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/07 14:44:45 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* philo_id != philo_pos (relative position of the philosopher in the array)
 * philo_pos = philo_id - 1 
 * 
 * In a circular table with 5 philosophers:
 * the 5th philosopher (philo_id = 5) is at position 4 (philo_pos = 4)
 * 	left_fork = [philo_pos] = 4
 * 	right_fork = [philo_pos + 1] % num_philo = 0
 *	[4 + 1] % 5 = 0
 */

static void	assign_forks(int philo_pos, t_data *data)
{
	if (philo_pos % 2 == 0)
	{
		data->philos[philo_pos].first_fork = &(data->forks[philo_pos]);
		data->philos[philo_pos].second_fork = &(data->forks[(philo_pos + 1)
				% data->num_philo]);
	}
	else
	{
		data->philos[philo_pos].first_fork = &(data->forks[(philo_pos + 1)
				% data->num_philo]);
		data->philos[philo_pos].second_fork = &(data->forks[philo_pos]);
	}
}

static void	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->num_philo)
	{
		philo = &(data->philos[i]);
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal = 0;
		philo->full = false;
		assign_forks(i, data);
		safe_mutex(INIT, &(philo->philo_mutex));
		philo->data = data;
		i++;
	}
}

void	init_data(t_data *data, char **argv)
{
	int	i;

	data->num_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->end_simulation = false;
	if (argv[5])
		data->meals_required = ft_atol(argv[5]);
	else
		data->meals_required = -1;
	data->all_threads_created = false;
	data->forks = safe_malloc(sizeof(t_fork) * data->num_philo);
	data->philos = safe_malloc(sizeof(t_philo) * data->num_philo);
	safe_mutex(INIT, &(data->data_mutex));
	safe_mutex(INIT, &(data->print_mutex));
	i = 0;
	while (i < data->num_philo)
	{
		data->forks[i].fork_id = i + 1;
		safe_mutex(INIT, &(data->forks[i].fork_mutex));
		i++;
	}
	init_philos(data);
}
