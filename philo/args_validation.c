/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:23:35 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/03 16:14:15 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	error_message(void)
{
	printf("Correct Usage: ./philo\n");
	printf("Mandatory parameters:\n");
	printf("[1][number_of_philosophers]\n");
	printf("[2][time_to_die]\n");
	printf("[3][time_to_eat]\n");
	printf("[4][time_to_sleep]\n");
	printf("Optional parameter:\n");
	printf("[5][number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

void	args_validation(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				exit(printf("Arguments must be digits only.\n"));
			if (ft_atol(argv[i]) > 2147483647)
				exit(printf("Arguments must not exceed the maximum integer value.\n"));
			j++;
		}
		j = 0;
		i++;
	}
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
		exit(printf("One to two hundread philosophers are required.\n"));
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60 || ft_atol(argv[4]) < 60)
		exit(printf("The time must be at least 60ms.\n"));
	if (argc == 6 && ft_atol(argv[5]) < 1)
		exit(printf("Philosophers must eat at least once.\n"));
}
