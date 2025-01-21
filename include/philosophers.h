/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:19:55 by judenis           #+#    #+#             */
/*   Updated: 2025/01/14 20:34:07 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H_
# define PHILOSOPHERS_H_

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    int id;
    int last_meal;
    int meals_eaten;
    bool is_dead;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
    pthread_mutex_t *eat_lock;
    struct s_data   *data;    
}               t_philo;

typedef struct s_data
{
    int number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_meals;
    t_philo *philo;
}               t_data;

#endif