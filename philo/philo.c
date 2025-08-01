/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:14:27 by mozahnou          #+#    #+#             */
/*   Updated: 2025/08/01 21:21:10 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	select_things(t_data *data, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->opt_arg = 0;
	data->all_eat = 0;
	data->death = 0;
	if (av[5])
		data->opt_arg = ft_atoi(av[5]);
}

int	is_valid_argument(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_space_num(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	validate_arguments_content(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_valid_argument(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_argument(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	if (validate_arguments_content(ac, av))
		return (1);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		return (1);
	if (ft_atoi(av[2]) < 60)
		return (1);
	if (ft_atoi(av[3]) < 60)
		return (1);
	if (ft_atoi(av[4]) < 60)
		return (1);
	if (ac == 6 && ft_atoi(av[5]) < 1)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (check_argument(ac, av))
	{
		printf("Invalid Arguments\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	select_things(data, av);
	if (!initialize_data(data))
		return (1);
	if (start_simulation(data))
		return (1);
	join_threads(data);
	free_and_destroy(data);
	return (0);
}
