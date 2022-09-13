/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomathi <thomathi@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:08:29 by thomathi          #+#    #+#             */
/*   Updated: 2022/09/13 14:08:29 by thomathi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

struct	s_rules;

typedef struct s_philosopher
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[200];
	pthread_mutex_t		writing;
	pthread_t			all_eat_cheaker;
	t_philosopher		philosophers[200];
}						t_rules;

/*
** ----- error_manager.c -----
*/

int						error_manager(int error);

/*
** ----- init.c -----
*/

int						ft_init_rules(int nbr_arg, char **str_arg, t_rules *r);
int						init_mutex(t_rules *r);
int						init_philo(t_rules *r);
/*
** ----- utils.c -----
*/

int						ft_atoi(const char *str);
void					action_print(t_rules *rules, int id, char *string);
long long				timestamp(void);
long long				time_diff(long long past, long long pres);
void					time_to_do(long long time, t_rules *rules);

/*
** ----- launcher.c -----
*/

void					start_eating(t_philosopher *p);
void					death_checker(t_rules *r);
void					*pthread(void *struct_philo);
int						start(t_rules *rules);
void					exit_start(t_rules *rules, t_philosopher *philos);
void					*dinner_checker(void	*void_rules);
void					exit_launcher(t_rules *rules, t_philosopher *philos);
#endif
