#include "philo.h"

int	init_data_philo(t_data *data)
{
	int i;

	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time();
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (0);
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (1);
}

void	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death_check, NULL);
}

int	initialize_data(t_data *data)
{
	if (!init_forks(data))
		return (0);
	if (!init_data_philo(data))
		return (0);
	init_mutex(data);
	return (1);
}
