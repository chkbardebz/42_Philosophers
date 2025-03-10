/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:03:07 by judenis           #+#    #+#             */
/*   Updated: 2025/03/06 12:52:55 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating_process(t_philo *philo, t_data *data)
{
	lock_forks(philo, data);
	pthread_mutex_lock(&(data->eating_lock));
	clean_printf(data, philo->id, "is eating");
	philo->last_meal = timestamp();
	(philo->meals_eaten)++;
	pthread_mutex_unlock(&(data->eating_lock));
	ft_dodo(data->time_to_eat, data);
	if (philo->id % 2 == 0)
		unlock_even(philo, data);
	else
		unlock_odd(philo, data);
}

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	eating_process(philo, data);
}

//! peut etre cause pb de performances
int	sleeping(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->death_lock));
	if (data->has_all_eaten == true)
	{
		pthread_mutex_unlock(&(data->death_lock));
		return (1);
	}
	pthread_mutex_unlock(&(data->death_lock));
	clean_printf(data, philo->id, "is sleeping");
	ft_dodo(data->time_to_sleep, data);
	clean_printf(data, philo->id, "is thinking");
	ft_dodo((data->time_to_eat > data->time_to_sleep) * (data->time_to_eat
			- data->time_to_sleep) + 1, data);
	return (0);
}

void	*routine_one(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&(data->death_lock));
		if (data->has_died == true)
		{
			pthread_mutex_unlock(&(data->death_lock));
			break ;
		}
		pthread_mutex_unlock(&(data->death_lock));
		pthread_mutex_lock(&(data->forks[philo->left]));
		clean_printf(data, philo->id, "has taken a fork");
		ft_dodo(data->time_to_die + 10, data);
		pthread_mutex_unlock(&(data->forks[philo->left]));
	}
	return (NULL);
}

int	routine_launch_one(t_data *data, t_philo *philo)
{
	if (pthread_create(&(philo[0].t_id), NULL, routine_one, &(philo[0])))
		return (1);
	pthread_mutex_lock(&(data->eating_lock));
	philo[0].last_meal = timestamp();
	pthread_mutex_unlock(&(data->eating_lock));
	is_dead(data, data->philo);
	exit_routine(data, philo);
	return (0);
}
