/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:21:41 by judenis           #+#    #+#             */
/*   Updated: 2025/02/05 12:19:55 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_routine(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philo)
		pthread_join(philo[i].t_id, NULL);
	i = -1;
	while (++i < data->number_of_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->printing));
	free(data->forks);
	free(data->philo);
}

void	is_dead(t_data *data, t_philo *philo)
{
	int	i;

	while (data->has_all_eaten == false)
	{
		i = -1;
		while (++i < data->number_of_philo && data->has_died == false)
		{
			pthread_mutex_lock(&(data->eating_lock));
			if ((timestamp() - philo[i].last_meal) > data->time_to_die)
				if_dead(data, philo, i);
			pthread_mutex_unlock(&(data->eating_lock));
			usleep(100);
		}
		pthread_mutex_lock(&(data->death_lock));
		if (data->has_died == true)
		{
			pthread_mutex_unlock(&(data->death_lock));
			break ;
		}
		pthread_mutex_unlock(&(data->death_lock));
		i = 0;
		pthread_mutex_lock(&(data->eating_lock));
		while (data->number_of_meals != -1 && i < data->number_of_philo
			&& philo[i].meals_eaten >= data->number_of_meals)
		{
			i++;
		}
			pthread_mutex_unlock(&(data->eating_lock));
		if (i == data->number_of_philo)
		{
			pthread_mutex_lock(&(data->death_lock));
			data->has_all_eaten = 1;
			pthread_mutex_unlock(&(data->death_lock));
		}
	}
}

void	eating(t_philo *philo)
{
	t_data	*data;
	int		first_fork;
	int		second_fork;

	data = philo->data;
	if (philo->left < philo->right)
	{
		first_fork = philo->left;
		second_fork = philo->right;
	}
	else
	{
		first_fork = philo->right;
		second_fork = philo->left;
	}
	pthread_mutex_lock(&(data->forks[first_fork]));
	clean_printf(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[second_fork]));
	clean_printf(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->eating_lock));
	clean_printf(data, philo->id, "is eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(data->eating_lock));
	ft_dodo(data->time_to_eat, data);
	pthread_mutex_lock(&(data->eating_lock));
	(philo->meals_eaten)++;
	pthread_mutex_unlock(&(data->eating_lock));
	pthread_mutex_unlock(&(data->forks[second_fork]));
	pthread_mutex_unlock(&(data->forks[first_fork]));
}

void	*routine(void *arg)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&(data->death_lock));
		if (data->has_died == true)
		{
			pthread_mutex_unlock(&(data->death_lock));
			break ;
		}
		pthread_mutex_unlock(&(data->death_lock));
		eating(philo);
		pthread_mutex_lock(&(data->death_lock));
		if (data->has_all_eaten == true)
		{
			pthread_mutex_unlock(&(data->death_lock));
			break ;
		}
		pthread_mutex_unlock(&(data->death_lock));
		clean_printf(data, philo->id, "is sleeping");
		ft_dodo(data->time_to_sleep, data);
		clean_printf(data, philo->id, "is thinking");
		i++;
	}
	return (NULL);
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
		ft_dodo(data->time_to_die + 2 , data);
		pthread_mutex_unlock(&(data->forks[philo->left]));
	}
	return (NULL);
}

int	routine_launch(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	data->start_time = timestamp();
	if (data->number_of_philo == 1)
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
	while (i < data->number_of_philo)
	{
		if (pthread_create(&(philo[i].t_id), NULL, routine, &(philo[i])))
			return (1);
		pthread_mutex_lock(&(data->eating_lock));
		philo[i].last_meal = timestamp();
		pthread_mutex_unlock(&(data->eating_lock));
		i++;
	}
	is_dead(data, data->philo);
	exit_routine(data, philo);
	return (0);
}
