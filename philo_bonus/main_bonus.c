/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:52:17 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 10:41:46 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink


The child does not inherit semaphore  adjustments  from  its  parent

 The child process is created  with  a  single  thread—the  one  that
          called  fork().   The  entire virtual address space of the parent is
          replicated in the child, including the states of mutexes,  condition
          variables,  and other pthreads objects; the use of pthread_atfork(3)
          may be helpful for dealing with problems that this can cause.

*/


int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		error_message();
	args_validation(argc, argv);
	init_data(&data, argv);
	father_process(&data);
	cleanup(&data);
}
