/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:21:41 by judenis           #+#    #+#             */
/*   Updated: 2025/01/21 18:09:41 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

void exit_routine(t_data *data, t_philo *philo)
{
    int i;
    
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

void death_check(t_data *data, t_philo *philo)
{
    int i;
    
    while (!(data->has_all_eaten))
    {
        i = -1;
        while (++i < data->number_of_philo && !(data->has_died))
        {
            pthread_mutex_lock(&(data->meal_check));
            if (time_diff(philo[i].last_meal, timestamp()) > data->time_to_die)
            {
                clean_printf(data, i, "has died\n");
                data->has_died = true;
            }
            pthread_mutex_unlock(&(data->meal_check));
            usleep(100);
        }
        if (data->has_died)
            break;
        i = 0;
        while (data->number_of_meals != -1 && i < data->number_of_philo && philo[i].meals_eaten >= data->number_of_meals)
            i++;
        if (i == data->number_of_philo)
            data->has_all_eaten = 1; 
    }
}

void eating(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(&(data->forks[philo->left]));
    clean_printf(data, philo->id, "has taken a fork");
    pthread_mutex_lock(&(data->forks[philo->right]));
    clean_printf(data, philo->id, "has taken a fork");
    pthread_mutex_lock(&(data->meal_check));
    clean_printf(data, philo->id, "is eating");
    philo->last_meal = timestamp();
    pthread_mutex_unlock(&(data->meal_check));
    smart_sleep(data->time_to_eat, data);
    (philo->meals_eaten)++;
    pthread_mutex_unlock(&(data->forks[philo->left]));
    pthread_mutex_unlock(&(data->forks[philo->right]));
}

void *routine(void *arg)
{
    int i;
    t_philo *philo;
    t_data *data;

    i = 0;
    philo = (t_philo *)arg;
    data = philo->data;
    if (philo->id % 2)
        usleep(15000);
    while (data->has_died == false)
    {
        eating(philo);
        if (data->has_all_eaten)
            break;
        clean_printf(data, philo->id, "is sleeping");
        smart_sleep(data->time_to_sleep, data);
        clean_printf(data, philo->id, "is thinking");
        i++;
    }
    return NULL;
}

int routine_launch(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    philo = data->philo;
    data->start_time = timestamp();
    while (i < data->number_of_philo)
    {
        if (pthread_create(&(philo[i].t_id), NULL, routine, &(philo[i])))
            return (1);
        philo[i].last_meal = timestamp();
        i++;
    }
    death_check(data, data->philo);
    exit_routine(data, philo);
    return (0);
}