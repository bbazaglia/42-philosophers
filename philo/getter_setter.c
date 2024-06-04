/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:50 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/04 16:40:39 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mtx, bool *var, bool value)
{
	safe_mutex(LOCK, mtx);
	*var = value;
	safe_mutex(UNLOCK, mtx);
}

void	get_bool(t_mtx *mtx, bool *var)
{
	bool	value;

	safe_mutex(LOCK, mtx);
	value = *var;
	safe_mutex(UNLOCK, mtx);
	return (value);
}

void	set_long(t_mtx *mtx, long *var, long value)
{
	safe_mutex(LOCK, mtx);
	*var = value;
	safe_mutex(UNLOCK, mtx);
}

void	get_long(t_mtx *mtx, long *var)
{
	long	value;

	safe_mutex(LOCK, mtx);
	value = *var;
	safe_mutex(UNLOCK, mtx);
	return (value);
}

bool	simulation_finished(t_data *data)
{
	return (get_bool(&(data->data_mutex), &(data->send_simulation)));
}
