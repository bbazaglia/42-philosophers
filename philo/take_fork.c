/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:23:16 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/07 15:16:45 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	safe_mutex(LOCK, &philo->first_fork->fork_mutex);
	safe_print(philo, TOOK_FIRST_FORK, false);
	safe_mutex(LOCK, &philo->second_fork->fork_mutex);
	safe_print(philo, TOOK_SECOND_FORK, false);
}

void	return_forks(t_philo *philo)
{
	safe_mutex(UNLOCK, &philo->first_fork->fork_mutex);
	safe_mutex(UNLOCK, &philo->second_fork->fork_mutex);
}
