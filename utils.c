/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:51:48 by bbazagli          #+#    #+#             */
/*   Updated: 2024/05/31 17:52:53 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	char	*nbr;
	int		i;
	int		sign;
	int		res;

	nbr = (char *)nptr;
	i = 0;
	sign = 1;
	res = 0;
	while (nbr[i] == 32 || (nbr[i] >= 9 && nbr[i] <= 13))
	{
		i++;
	}
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		res = res * 10 + nbr[i] - '0';
		i++;
	}
	return (res * sign);
}

int	error_message(void)
{
	printf("Corect Usage: ./philo\n");
	printf("Mandatory parameters:\n");
	printf("[1][number_of_philosophers]\n");
	printf("[2][time_to_die]\n");
	printf("[3][time_to_eat]\n");
	printf("[4][time_to_sleep]\n");
	printf("Optional parameter:\n");
	printf("[5][number_of_times_each_philosopher_must_eat]\n");
	return (EXIT_FAILURE);
}