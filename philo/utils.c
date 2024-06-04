/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:51:48 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/04 17:14:36 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (simulation_finished(data))
		return ;
	safe_mutex(LOCK, &(data->write_mutex));
	if (status == EATING)
		printf(B "%ld %d is eating" RST "\n", get_time_diff(data->start_time),
				philo->id);
	else if (status == SLEEPING)
		printf(G "%ld %d is sleeping" RST "\n", get_time_diff(data->start_time),
				philo->id);
	else if (status == THINKING)
		printf(Y "%ld %d is thinking" RST "\n", get_time_diff(data->start_time),
				philo->id);
	else if (status == TOOK_FIRST_FORK || status == TOOK_SECOND_FORK)
		printf(W "%ld %d has taken a fork" RST "\n",
				get_time_diff(data->start_time), philo->id);
	else if (status == DEAD)
		printf(RED "%ld %d died" RST "\n", get_time_diff(data->start_time),
				philo->id);
	safe_mutex(UNLOCK, &(data->write_mutex));
}

long	ft_atol(char *str)
{
	long	nb;
	long	sign;

	nb = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
		nb = nb * 10 + (*str++ - '0');
	return (nb * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// void	cleanup(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->num_philo)
// 	{
// 		pthread_mutex_destroy(&(data->forks[i]));
// 		free(data->philo[i].thread);
// 		i++;
// 	}
// 	free(data->forks);
// 	data->forks = NULL;
// 	free(data->philo);
// 	data->philo = NULL;
// 	free(data);
// }
