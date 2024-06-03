/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:52:04 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/03 16:38:41 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	int				meals_eaten;
	t_data *data
}					t_philo;

typedef struct s_data
{
	long			start_time;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	bool			end_simulation;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
}					t_data;

long				ft_atol(char *str);
int					ft_isdigit(int c);
void				init_data(t_data **data, char **argv);
void				init_philos(t_data *data);
void				args_validation(int argc, char **argv);
long				get_time_in_ms(void);
void				cleanup(t_data *data);

#endif