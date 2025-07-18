#ifndef PHILO_BONUS
#define PHILO_BONUS

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>

typedef struct s_data
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		opt_arg;
	long long	start_time;

	sem_t	*sem_forks;
	sem_t	*sem_print;
	sem_t	*sem_dead;
	int		*death_flag;
} t_data;

typedef struct s_philo
{
	int		id;
	pid_t	pid;
	long long	last_meal;
	int		meals_eaten;
	t_data	*data;
} t_philo;



#endif
