/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:52:22 by judenis           #+#    #+#             */
/*   Updated: 2025/01/21 17:36:59 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void clean_printf(t_data *data, int id, char *str)
{
    pthread_mutex_lock(&(data->printing));
    if (data->has_died == false)
    {
        printf("%lli ", timestamp() - data->start_time);
        printf("%i ", id + 1);
        printf("%s\n", str);
    }
    pthread_mutex_unlock(&(data->printing));
    return ;
}

long long timestamp(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


void smart_sleep(long long time, t_data *data)
{
    long long i;
    
    i = timestamp();
    while ((data->has_died) == false)
    {
        if (time_diff(i, timestamp()) >= time)
            break;
        usleep(50);
    }
}