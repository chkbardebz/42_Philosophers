/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:51:38 by judenis           #+#    #+#             */
/*   Updated: 2025/03/06 12:54:06 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock_even(t_philo *philo, t_data *data)
{
	if (philo->l_lock == true)
	{
		pthread_mutex_unlock(&(data->forks[philo->left]));
		philo->l_lock = false;
	}
	if (philo->r_lock == true)
	{
		pthread_mutex_unlock(&(data->forks[philo->right]));
		philo->r_lock = false;
	}
}

void	unlock_odd(t_philo *philo, t_data *data)
{
	if (philo->r_lock == true)
	{
		pthread_mutex_unlock(&(data->forks[philo->right]));
		philo->r_lock = false;
	}
	if (philo->l_lock == true)
	{
		pthread_mutex_unlock(&(data->forks[philo->left]));
		philo->l_lock = false;
	}
}

void	lock_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(data->forks[philo->left]));
		philo->l_lock = true;
		clean_printf(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&(data->forks[philo->right]));
		philo->r_lock = true;
		clean_printf(data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(data->forks[philo->right]));
		philo->r_lock = true;
		clean_printf(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&(data->forks[philo->left]));
		philo->l_lock = true;
		clean_printf(data, philo->id, "has taken a fork");
	}
}
