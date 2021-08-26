/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:08:39 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/25 14:59:10 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", \
		get_time() - philo->data->start_time, philo->num + 1, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	print_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d died\n", \
		get_time() - philo->data->start_time, philo->num + 1);
}

long	get_time(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

void	free_all(t_philo *philos, t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	if (philos)
		free(philos);
}

int	exit_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
