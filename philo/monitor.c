#include "philo.h"

void	edit_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_check);
	philo->data->death = 1;
	pthread_mutex_unlock(&philo->data->death_check);
}

int	check_philo_death(t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->data->meals_check);
	now = get_time();
	if (now - philo->last_meal >= philo->data->time_die)
	{
		pthread_mutex_unlock(&philo->data->meals_check);
		print_status(philo, "is died");
		edit_death(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meals_check);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		full;

	data = (t_data *)arg;
	while (data->num_philo)
	{
		i = 0;
		full = 0;
		while (i < data->num_philo)
		{
			if (check_philo_death(&data->philos[i]))
				return (NULL);
			pthread_mutex_lock(&data->meals_check);
			if (data->opt_arg && data->philos[i].meals_eaten >= data->opt_arg)
    			full++;
			pthread_mutex_unlock(&data->meals_check);
			i++;
		}
		if (data->opt_arg && full == data->num_philo)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

