/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:52:04 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/07 15:11:36 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PAUSE 100
#define DEBUG true

/*-------------------ANSI Escape Sequences for Bold Text Colors--------------*/
# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m"   /* Bold Green */
# define Y "\033[1;33m"   /* Bold Yellow */
# define B "\033[1;34m"   /* Bold Blue */
# define M "\033[1;35m"   /* Bold Magenta */
# define C "\033[1;36m"   /* Bold Cyan */
# define W "\033[1;37m"   /* Bold White */

/*-------------------STRUCTS-------------------------------------------------*/

typedef pthread_mutex_t	t_mtx;

typedef struct s_data	t_data;

typedef enum e_action
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_action;

enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TOOK_FIRST_FORK,
	TOOK_SECOND_FORK,
	DEAD,
};

typedef struct s_fork
{
	t_mtx				fork_mutex;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_eaten;
	long				last_meal;
	bool				full;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					num_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_required;
	long				start_time;
	bool				end_simulation;
	bool				all_threads_created;
	t_fork				*forks;
	t_philo				*philos;  // array of t_philo structs
	t_mtx				data_mutex;
	t_mtx				print_mutex;
}						t_data;

/*-------------------FUNCTIONS-----------------------------------------------*/

/*-------------------PARSE INPUT---------------------------------------------*/
void					args_validation(int argc, char **argv);
void					init_data(t_data *data, char **argv);

/*-------------------SAFE FUNCTIONS------------------------------------------*/
void					*safe_malloc(size_t size);
void					safe_thread(t_action action, pthread_t *thread,
							void *(*routine)(void *), t_philo *philo);
void					safe_mutex(t_action action, t_mtx *mtx);
void					safe_print(t_philo *philo, int status, bool debug);

/*-------------------GETTERS AND SETTERS-------------------------------------*/
void					set_bool(t_mtx *mtx, bool *var, bool value);
long					get_bool(t_mtx *mtx, bool *var);
void					set_long(t_mtx *mtx, long *var, long value);
long					get_long(t_mtx *mtx, long *var);

/*-------------------ROUTINE-------------------------------------------------*/
void					start_simulation(t_data *data);
void					eat(t_philo *philo);
void					think(t_philo *philo);
void					rest(t_philo *philo);
void					take_forks(t_philo *philo);
void					return_forks(t_philo *philo);

/*-------------------MONITOR-------------------------------------------------*/
bool					simulation_finished(t_data *data);
void 					*monitor(void *data_ptr);

/*-------------------WRITE STATUS--------------------------------------------*/
void					write_status(int status, t_philo *philo);
void					write_debug_status(int status, t_philo *philo);

/*-------------------TIME----------------------------------------------------*/
long					get_time_in_ms(void);
long					timestamp(long start_time);

/*-------------------UTILS---------------------------------------------------*/
long					ft_atol(char *str);
int						ft_isdigit(int c);
void					cleanup(t_data *data);
void					error_message(void);

#endif