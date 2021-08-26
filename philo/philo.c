/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 10:35:44 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/26 13:25:07 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_philos(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->args->num_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	return (0);
}

int	init_philos(t_philo *philos, t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->args->num_philos)
	{
		philos[i].num = i;
		philos[i].data = data;
	}
	data->start_time = get_time();
	if (pthread_create(&data->monitor, NULL, &monitor, philos))
		return (exit_error("Thread create error\n"));
	i = -1;
	while (++i < data->args->num_philos)
	{
		if (pthread_create(&data->philos[i], NULL, &simulation, &philos[i]))
			return (exit_error("Thread create error\n"));
		pthread_detach(data->philos[i]);
		usleep(1000);
	}
	pthread_join(data->monitor, NULL);
	return (end_philos(data));
}

int	init_data(t_data *data, t_args *args, t_philo **philos)
{
	int		i;

	data->args = args;
	*philos = (t_philo *)malloc(sizeof(t_philo) * args->num_philos);
	data->philos = (pthread_t *)malloc(sizeof(pthread_t) * args->num_philos);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* args->num_philos);
	if (!*philos || !data->philos || !data->forks)
		return (exit_error("Memory allocation error\n"));
	memset(*philos, 0, sizeof(t_philo) * args->num_philos);
	memset(data->philos, 0, sizeof(pthread_t) * args->num_philos);
	memset(data->forks, 0, sizeof(pthread_mutex_t) * args->num_philos);
	i = -1;
	while (++i < data->args->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (exit_error("Mutex init error\n"));
	}
	if (pthread_mutex_init(&data->data_mutex, NULL))
		return (exit_error("Mutex init error\n"));
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (exit_error("Mutex init error\n"));
	return (0);
}

int	init_args(t_args *args, int argc, char **argv)
{
	int		i;

	if (argc != 5 && argc != 6)
		return (exit_error("Invalid number of arguments\n"));
	i = 0;
	while (++i < argc)
	{
		if (ft_strisdigit(argv[i]))
			return (exit_error("Invalid argument\n"));
	}
	args->num_philos = ft_atoi(argv[1]);
	args->time_die = ft_atoi(argv[2]);
	args->time_eat = ft_atoi(argv[3]);
	args->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->num_eats = ft_atoi(argv[5]);
	else
		args->num_eats = -1;
	if (args->num_philos <= 0 || args->num_philos > INT_MAX \
		|| args->time_die <= 0 || args->time_die > INT_MAX \
		|| args->time_eat <= 0 || args->time_eat > INT_MAX \
		|| args->time_sleep <= 0 || args->time_sleep > INT_MAX \
		|| (argc == 6 && (args->num_eats <= 0 || args->num_eats > INT_MAX)))
		return (exit_error("Invalid argument\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		args;
	t_data		data;
	t_philo		*philos;

	memset(&args, 0, sizeof(t_args));
	memset(&data, 0, sizeof(t_data));
	philos = NULL;
	if (init_args(&args, argc, argv))
		return (1);
	if (init_data(&data, &args, &philos))
	{
		free_all(philos, &data);
		return (1);
	}
	if (init_philos(philos, &data))
	{
		free_all(philos, &data);
		return (1);
	}
	free_all(philos, &data);
	return (0);
}
