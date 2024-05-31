/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:52:17 by bbazagli          #+#    #+#             */
/*   Updated: 2024/05/31 17:53:03 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int argc, char **argv)
{
	t_data *data;
	pthread_t thread[ft_atoi(argv[1])];

	init_data(data, argv);

	// pthread_mutex_t mutex;
	// pthread_mutex_init(&mutex, NULL);
	if (argc != 5 && argc != 6)
		error_message();
	// if (pthread_create(&thread, NULL, &routine, &mutex) != 0)
	// 	return (EXIT_FAILURE);
	// pthread_mutex_destroy(&mutex);
}