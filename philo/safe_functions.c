/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:19:57 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/11 09:35:21 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(printf("Malloc error\n"));
	return (ptr);
}

void	safe_mutex(t_action action, t_mtx *mtx)
{
	int	status;

	status = 0;
	if (action == LOCK)
		status = pthread_mutex_lock(mtx);
	else if (action == UNLOCK)
		status = pthread_mutex_unlock(mtx);
	else if (action == INIT)
		status = pthread_mutex_init(mtx, NULL);
	else if (action == DESTROY)
		status = pthread_mutex_destroy(mtx);
	if (status)
		exit(printf("Mutex error\n"));
}

void	safe_thread(t_action action, pthread_t *thread,
		void *(*routine)(void *), t_philo *philo)
{
	int	status;

	status = 0;
	if (action == CREATE)
		status = pthread_create(thread, NULL, routine, philo);
	else if (action == JOIN)
		status = pthread_join(*thread, NULL);
	else if (action == DETACH)
		status = pthread_detach(*thread);
	if (status)
		exit(printf("Thread error\n"));
}

void	safe_print(t_philo *philo, int status, bool debug)
{
	t_data	*data;

	data = philo->data;
	if (simulation_finished(data))
		return ;
	safe_mutex(LOCK, &(data->print_mutex));
	if (debug)
		write_debug_status(status, philo);
	else
		write_status(status, philo);
	safe_mutex(UNLOCK, &(data->print_mutex));
}
