/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:14:36 by mozahnou          #+#    #+#             */
/*   Updated: 2025/08/01 21:26:53 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	free_and_destroy(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_philo)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death_check);
	pthread_mutex_destroy(&data->meals_check);
}

int	ft_space_num(char c)
{
	if (c == 32 || (c >= 9 && c <= 13) 
		|| c == '+' || (c >= '0' && c <= '9'))
		return (0);
	return (1);
}

void	ft_usleep(long long time, t_philo *philo)
{
	long long	start;

	start = get_time();
	while (!is_dead(philo) && get_time() - start < time)
		usleep(500);
}
