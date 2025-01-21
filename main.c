/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:17:10 by judenis           #+#    #+#             */
/*   Updated: 2025/01/21 18:17:25 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

//? number_of_philosophers 
//? time_to_die 
//? time_to_eat
//? time_to_sleep
//? [number of time each philo needs to eat]

//* EAT
//* SLEEP
//* THINK
//* REPEAT (WHILE NOBODY IS DEAD OR WHILE EVERYONE HASN'T EATEN THE AMOUNT OF TIMES REQUIRED)


int	ft_isspace(int c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}

int init_philo(t_data *data)
{
    int i;

    i = data->number_of_philo;
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
    if (data->philo == NULL)
        return (1);
    while (--i >= 0)
    {
        data->philo[i].id = i;
        data->philo[i].last_meal = 0;
        data->philo[i].meals_eaten = 0;
        data->philo[i].left = i;
        data->philo[i].right = (i + 1) % data->number_of_philo;
        data->philo[i].data = data;
    }
    return (0);
}

int init_forks(t_data *data)
{
    int i;
    
    i = data->number_of_philo;
    data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
    if (data->forks == NULL)
        return (1);
    while (--i >= 0)
    {
        if (pthread_mutex_init(&(data->forks[i]), NULL))
            return (1);
    }
	if (pthread_mutex_init(&(data->printing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (1);
    return (0);
}

int data_init(t_data *data, char **av)
{
    data->start_time = 0;
    data->number_of_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->has_died = 0;
    data->has_all_eaten = 0;
    if (data->number_of_philo < 1 || data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
        return (1);
    if (av[5])
    {
        data->number_of_meals = ft_atoi(av[5]) - 1;
        if (data->number_of_meals <= 0)
            return (1);
    }
    else
        data->number_of_meals = -1;
    if (init_forks(data))
        return (1);
    init_philo(data);
    return (0);
}

int main(int ac, char **av)
{
    t_data data;
   
    printf("%lli \n\n", time_diff(timestamp(), timestamp()));
    if (ac < 5 || ac > 6)
        return (write(2, "Error\nInvalid number of arguments\n", 35));
    if (check_args(av) == 1)
        return (write(2, "Error\nInvalid arguments\n", 25));
    if (data_init(&data, av) == 1)
        return (write(2, "Error\nThread error\n", 20));
    if (routine_launch(&data) == 1)
        return (write(2, "Error\nThread error\n", 20));
}
