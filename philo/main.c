/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:52:17 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/07 15:18:40 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO: implement think and sleep functions
// TODO: implement monitor function
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		error_message();
	args_validation(argc, argv);
	init_data(&data, argv);
	start_simulation(&data);
	cleanup(&data);
}
