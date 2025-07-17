#include "philo.h"

int	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitor_routine, data) != 0)
		return (1);
	return (0);
}

void	join_threads(t_data *data)
{
	int	i = 0;

	while (i < data->num_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}
