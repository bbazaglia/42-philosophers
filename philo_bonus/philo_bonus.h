/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:52:04 by bbazagli          #+#    #+#             */
/*   Updated: 2024/06/17 17:58:28 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

/*-------------------ANSI Escape Sequences for Bold Text Colors--------------*/
# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m"   /* Bold Green */
# define Y "\033[1;33m"   /* Bold Yellow */
# define B "\033[1;34m"   /* Bold Blue */
# define M "\033[1;35m"   /* Bold Magenta */
# define C "\033[1;36m"   /* Bold Cyan */
# define W "\033[1;37m"   /* Bold White */

# define PAUSE 1000
# define DEBUG 0

/*-------------------STRUCTS-------------------------------------------------*/

typedef pthread_mutex_t	t_mtx;

typedef struct s_data	t_data;

enum					e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TOOK_FIRST_FORK,
	TOOK_SECOND_FORK,
	DEAD,
	FULL,
};

typedef struct s_philo
{
	int					id;
	long				meals_eaten;
	long 				last_meal;
	sem_t				*last_meal_sem;
	pid_t				pid;
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
	long				simulation_finished;
	sem_t				*end_simulation;
	sem_t				*forks_sem;
	sem_t				*print_sem;
	sem_t				*death_sem;
	sem_t				*full_sem;
	pthread_t			death_monitor;
	pthread_t			fullness_monitor;
	t_philo				*philo;
}						t_data;

/*-------------------FUNCTIONS-----------------------------------------------*/

/*-------------------PARSE INPUT---------------------------------------------*/
void					args_validation(int argc, char **argv);

/*-------------------INIT DATA-----------------------------------------------*/
void					init_data(t_data *data, char **argv);
void					create_processes(t_data *data, int i);
void					create_philo_thread(t_philo *philo);
void					create_semaphores(t_data *data);
void					init_philos(t_data *data);

/*-------------------ROUTINE-------------------------------------------------*/
void					single_routine(t_data *data, t_philo *philo);
void					multiple_routine(t_philo *philo);
void					eat(t_philo *philo);
void					think(t_philo *philo);
void					rest(t_philo *philo);
void					take_forks(t_philo *philo);
void					return_forks(t_philo *philo);
void					father_process(t_data *data);
void					kill_child_proc(t_data *data);

/*-------------------MONITOR-------------------------------------------------*/
void					*monitor(void *arg);
void					init_monitor_threads(t_data *data);
void					end_monitor_threads(t_data *data);
void					end_simulation(t_data *data, int status);
void					*death_monitor(void *arg);
void					*fullness_monitor(void *arg);

/*-------------------SAFE FUNCTIONS------------------------------------------*/
long					is_simulation_finished(t_data *data);
void					safe_print(t_philo *philo, int status, bool debug);
long					safe_get(sem_t *sem, long *value);
void					safe_set(sem_t *sem, long *value, long new_value);

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