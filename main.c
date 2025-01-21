/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:17:10 by judenis           #+#    #+#             */
/*   Updated: 2025/01/14 20:32:21 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

//? number_of_philosophers 
//? time_to_die 
//? time_to_eat
//? time_to_sleep
//? [number of time each philo needs to eat]


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

t_data *data_init(int ac, char **av)
{
    t_data *data;
    
    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    data->number_of_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        data->number_of_meals = ft_atoi(av[5]);
    else
        data->number_of_meals = 0;
    return (data);
}

int check_args(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}

int main(int ac, char **av)
{
    t_data *data;
    pthread_t thread;
    
    if (ac < 5 || ac > 6)
        return (write(2, "Error\nInvalid number of arguments\n", 35));
    if (check_args(av) == 1)
        return (write(2, "Error\nInvalid arguments\n", 25));
    data = data_init(ac, av);
    pthread_create(&thread, NULL, routine_philo, data);
    printf("nbr of philo : %d\ntime to die : %d\ntime to eat : %d\ntime to sleep : %d\nnbr of meals : %d\n", data->number_of_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->number_of_meals);
}
