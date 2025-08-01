/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:14:24 by mozahnou          #+#    #+#             */
/*   Updated: 2025/08/01 21:24:25 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->data->death_check);
	dead = philo->data->death;
	pthread_mutex_unlock(&philo->data->death_check);
	return (dead);
}

void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	if (!is_dead(philo))
		printf("%lld %d %s\n",
			get_time() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	eat_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (philo->data->num_philo == 1)
	{
		ft_usleep(philo->data->time_die, philo);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meals_check);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meals_check);
	ft_usleep(philo->data->time_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_philo(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_sleep, philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo->data->num_philo != 1)
			print_status(philo, "is thinking");
		eat_philo(philo);
		if (philo->data->opt_arg && philo->meals_eaten == philo->data->opt_arg)
			break ;
		if (philo->data->num_philo == 1)
			break ;
		sleep_philo(philo);
		if (is_dead(philo))
			break ;
	}
	return (NULL);
}
