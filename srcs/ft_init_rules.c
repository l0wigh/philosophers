/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomathi <thomathi@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:08:07 by thomathi          #+#    #+#             */
/*   Updated: 2022/09/13 14:08:07 by thomathi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_rules(int nbr_arg, char **str_arg, t_rules *r)
{
	if (nbr_arg < 5 || nbr_arg > 6)
		return (1);
	r->nb_philo = ft_atoi(str_arg[1]);
	r->time_death = ft_atoi(str_arg[2]);
	r->time_eat = ft_atoi(str_arg[3]);
	r->time_sleep = ft_atoi(str_arg[4]);
	r->dieded = 0;
	r->all_ate = 0;
	if (r->nb_philo < 1 || r->time_death < 0 || r->time_eat <= 0
		|| r->time_sleep <= 0 || r->nb_philo > 250)
		return (1);
	if (str_arg[5])
	{
		r->nb_eat = ft_atoi(str_arg[5]);
		if (r->nb_eat <= 0)
			return (1);
	}
	else
		r->nb_eat = -1;
	if (init_mutex(r))
		return (2);
	init_philo(r);
	return (0);
}

int	init_mutex(t_rules *r)
{
	int	i;

	i = r->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(r->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(r->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(r->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philo(t_rules *r)
{
	int	i;

	i = r->nb_philo;
	while (--i >= 0)
	{
		r->philosophers[i].id = i;
		r->philosophers[i].x_ate = 0;
		r->philosophers[i].left_fork_id = i;
		r->philosophers[i].right_fork_id = (i + 1) % r->nb_philo;
		r->philosophers[i].t_last_meal = 0;
		r->philosophers[i].rules = r;
	}
	return (0);
}
