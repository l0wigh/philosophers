/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomathi <thomathi@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:08:13 by thomathi          #+#    #+#             */
/*   Updated: 2022/09/13 14:08:13 by thomathi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	main(int ac, char **av)
{
	int			error_code;
	t_rules		*r;

	r = malloc(sizeof(t_rules));
	error_code = ft_init_rules(ac, av, r);
	if (error_manager(error_code))
		return (1);
	if (start(r))
		return (printf("error thread\n"));
	return (0);
}

void	exit_launcher(t_rules *rules, t_philosopher *philos)
{
	int		i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	pthread_join(rules->all_eat_cheaker, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->meal_check));
}
