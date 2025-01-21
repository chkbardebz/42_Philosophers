/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:19:55 by judenis           #+#    #+#             */
/*   Updated: 2025/01/21 17:53:32 by judenis          ###   ########.fr       */
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
    long long last_meal;
    int meals_eaten;
    int left;
    int right;
    struct s_data   *data;
    pthread_t t_id;  
}               t_philo;

typedef struct s_data
{
    int number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_meals;
    long long start_time;
    bool has_died;
    bool has_all_eaten;
    pthread_mutex_t printing;
    pthread_mutex_t meal_check; //! A remplacer
    pthread_mutex_t *forks;
    t_philo *philo;
}               t_data;

int routine_launch(t_data *data);

long long	time_diff(long long past, long long pres);
int check_args(char **av);
void clean_printf(t_data *data, int id, char *str);
long long timestamp(void);
void smart_sleep(long long time, t_data *data);

#endif