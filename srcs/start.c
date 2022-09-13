/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomathi <thomathi@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:08:35 by thomathi          #+#    #+#             */
/*   Updated: 2022/09/13 14:08:35 by thomathi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	death_checker(t_rules *r)
{
	int	i;

	while (!r->dieded && !r->all_ate)
	{
		i = 0;
		while (i < r->nb_philo)
		{
			if (!r->dieded && time_diff(r->philosophers[i].t_last_meal,
					timestamp()) >= r->time_death)
			{
				action_print(r, r->philosophers[i].id, "dead");
				r->dieded = 1;
			}
			i++;
		}
		usleep(50);
	}
	return ;
}

void	start_eating(t_philosopher *p)
{
	t_rules	*r;

	r = p->rules;
	pthread_mutex_lock(&(r->forks[p->left_fork_id]));
	action_print(r, p->id, "has take left fork");
	pthread_mutex_lock(&(r->forks[p->right_fork_id]));
	action_print(r, p->id, "has take right fork");
	if (r->dieded)
		return ;
	action_print(r, p->id, "is eating");
	p->t_last_meal = timestamp();
	time_to_do(r->time_eat, r);
	p->x_ate++;
	pthread_mutex_unlock(&(r->forks[p->left_fork_id]));
	pthread_mutex_unlock(&(r->forks[p->right_fork_id]));
}

void	*pthread(void *struct_philo)
{
	t_philosopher	*p;
	t_rules			*r;

	p = (t_philosopher *)struct_philo;
	r = p->rules;
	if (p->id % 2)
		usleep(100);
	while (!r->dieded && !r->all_ate)
	{
		start_eating(p);
		if (r->all_ate || r->dieded)
			break ;
		action_print(r, p->id, "sleep");
		time_to_do(r->time_sleep, r);
		if (!r->dieded)
			action_print(r, p->id, "think");
	}
	return (NULL);
}

int	start(t_rules *r)
{
	int				i;
	t_philosopher	*p;

	p = r->philosophers;
	i = 0;
	r->first_timestamp = timestamp();
	while (i < r->nb_philo)
	{
		if (pthread_create(&(p[i].thread_id), NULL, pthread, &(p[i])))
			return (1);
		p[i].t_last_meal = timestamp();
		i++;
	}
	pthread_create(&(r->all_eat_cheaker), NULL, dinner_checker, r);
	death_checker(r);
	return (0);
}

void	*dinner_checker(void	*void_rules)
{
	t_rules			*r;
	int				i;
	t_philosopher	*p;

	r = (t_rules *)void_rules;
	p = r->philosophers;
	i = 0;
	while (!r->all_ate && !r->dieded)
	{
		while (i < r->nb_philo && (r->philosophers[i].x_ate == r->nb_eat))
			i++;
		usleep(50);
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
	exit_launcher(r, p);
	return (NULL);
}
