#include "philo.h"

int	check_philo_death(t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->data->death_check);
	now = get_time();
	if (now - philo->last_meal >= philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d died 💀\n", now - philo->data->start_time, philo->id);
		philo->data->death = 1;
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->death_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_check);
	return (0);
}

// void	*monitor_routine(void *arg)
// {
// 	t_data	*data = (t_data *)arg;
// 	int		i;

// 	while (!data->death)
// 	{
// 		i = 0;
// 		while (i < data->num_philo && !data->death)
// 		{
// 			if (check_philo_death(&data->philos[i]))
// 				break;
// 			i++;
// 		}
// 		usleep(1000); // avoid CPU 100%
// 	}
// 	return (NULL);
// }

void	*monitor_routine(void *arg)
{
	t_data	*data = (t_data *)arg;
	int		i;
	int		full;

	while (!data->death)
	{
		i = 0;
		full = 0;
		while (i < data->num_philo)
		{
			if (check_philo_death(&data->philos[i]))
				return (NULL);
			if (data->opt_arg && data->philos[i].meals_eaten >= data->opt_arg)
				full++;
			i++;
		}
		if (data->opt_arg && full == data->num_philo)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

