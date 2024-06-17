/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:19:57 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 17:51:40 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	safe_print(t_philo *philo, int status, bool debug)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->print_sem);
	if (debug)
		write_debug_status(status, philo);
	else
		write_status(status, philo);
	sem_post(data->print_sem);
}

long	safe_get(sem_t *sem, long *value)
{
	long	get_value;

	sem_wait(sem);
	get_value = *value;
	sem_post(sem);
	return (get_value);
}

void	safe_set(sem_t *sem, long *value, long new_value)
{
	sem_wait(sem);
	*value = new_value;
	sem_post(sem);
}
