/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:19:55 by judenis           #+#    #+#             */
/*   Updated: 2025/01/30 13:21:56 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meals_eaten;
	int				left;
	int				right;
	struct s_data	*data;
	pthread_t		t_id;
}					t_philo;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long long		start_time;
	bool			has_died;
	bool			has_all_eaten;
	pthread_mutex_t	printing;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	t_philo			*philo;
}					t_data;

int					routine_launch(t_data *data);

int					check_args(char **av);
void				clean_printf(t_data *data, int id, char *str);
long long			timestamp(void);
void				ft_dodo(long long time, t_data *data);
int					ft_atoi(const char *str);
void				if_dead(t_data *data, t_philo *philo, int i);

#endif