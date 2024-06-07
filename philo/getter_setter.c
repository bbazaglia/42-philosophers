/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:50 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/07 15:13:09 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mtx, bool *value, bool new_value)
{
	safe_mutex(LOCK, mtx);
	*value = new_value;
	safe_mutex(UNLOCK, mtx);
}

long	get_bool(t_mtx *mtx, bool *var)
{
	bool	value;

	safe_mutex(LOCK, mtx);
	value = *var;
	safe_mutex(UNLOCK, mtx);
	return (value);
}

void	set_long(t_mtx *mtx, long *value, long new_value)
{
	safe_mutex(LOCK, mtx);
	*value = new_value;
	safe_mutex(UNLOCK, mtx);
}

long	get_long(t_mtx *mtx, long *var)
{
	long	value;

	safe_mutex(LOCK, mtx);
	value = *var;
	safe_mutex(UNLOCK, mtx);
	return (value);
}
