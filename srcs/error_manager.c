/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomathi <thomathi@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:07:51 by thomathi          #+#    #+#             */
/*   Updated: 2022/09/13 14:07:53 by thomathi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_manager(int error)
{
	if (error == 1)
		return (printf("At least one wrong argument\n"));
	if (error == 2)
		return (printf("Fatal error when intializing mutex\n"));
	return (error);
}
