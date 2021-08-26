/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:08:39 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/26 00:23:26 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *status)
{
	sem_wait(philo->data->print_sem);
	printf("%ld %d %s\n", \
		get_time() - philo->data->start_time, philo->num + 1, status);
	sem_post(philo->data->print_sem);
}

void	print_died(t_philo *philo)
{
	sem_wait(philo->data->print_sem);
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
