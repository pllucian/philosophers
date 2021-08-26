/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:56:52 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/26 13:18:33 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[(philo->num + 1) % \
		philo->data->args->num_philos]);
	pthread_mutex_unlock(&philo->data->forks[philo->num]);
}

int	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->num]);
	print_status(philo, "has taken a fork");
	if (philo->data->args->num_philos < 2)
		return (1);
	pthread_mutex_lock(&philo->data->forks[(philo->num + 1) % \
		philo->data->args->num_philos]);
	print_status(philo, "has taken a fork");
	return (0);
}

void	*simulation(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_take_forks(philo))
			usleep(philo->data->args->time_die * 1000);
		print_status(philo, "is eating");
		philo->time_last_eat = get_time() - philo->data->start_time;
		usleep(philo->data->args->time_eat * 1000);
		philo_put_forks(philo);
		philo->num_eats++;
		if (philo->num_eats == philo->data->args->num_eats)
		{
			pthread_mutex_lock(&philo->data->data_mutex);
			philo->data->philos_eated++;
			pthread_mutex_unlock(&philo->data->data_mutex);
			break ;
		}
		print_status(philo, "is sleeping");
		usleep(philo->data->args->time_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo		*philos;
	long		time;
	int			i;

	philos = (t_philo *)arg;
	while (1)
	{
		if (philos->data->philos_eated == philos->data->args->num_philos)
			return (NULL);
		time = get_time() - philos->data->start_time;
		i = -1;
		while (++i < philos->data->args->num_philos)
		{
			if (time - philos[i].time_last_eat >= philos->data->args->time_die)
			{
				print_died(&philos[i]);
				return (NULL);
			}
		}
	}
	return (NULL);
}
