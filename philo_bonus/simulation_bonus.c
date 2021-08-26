/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:56:52 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/26 12:17:48 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_put_forks(t_philo *philo)
{
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
}

void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks_sem);
	print_status(philo, "has taken a fork");
}

void	*simulation(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_take_forks(philo);
		print_status(philo, "is eating");
		philo->time_last_eat = get_time() - philo->data->start_time;
		usleep(philo->data->args->time_eat * 1000);
		philo_put_forks(philo);
		philo->num_eats++;
		if (philo->num_eats == philo->data->args->num_eats)
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->data->args->time_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

int	philo_process(t_philo *philo)
{
	pthread_t	philo_thread;
	long		time;

	if (pthread_create(&philo_thread, NULL, &simulation, philo))
		return (exit_error("Thread create error\n"));
	pthread_detach(philo_thread);
	while (1)
	{
		if (philo->num_eats == philo->data->args->num_eats)
			break ;
		time = get_time() - philo->data->start_time;
		if (time - philo->time_last_eat >= philo->data->args->time_die)
		{
			print_died(philo);
			return (2);
		}
	}
	return (0);
}
