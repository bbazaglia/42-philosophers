/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:52:17 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/11 10:18:01 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		error_message();
	args_validation(argc, argv);
	init_data(&data, argv);
	start_simulation(&data);
	while (!simulation_finished(&data))
		monitor(&data);
	wait_threads_end(&data);
	cleanup(&data);
}
