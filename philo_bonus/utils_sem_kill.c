/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sem_kill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:17:20 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/26 11:39:51 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_pids(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->args->num_philos)
		kill(data->philos[i], SIGKILL);
}

void	end_sems(t_data *data)
{
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
}

void	init_sems(t_data *data, t_args *args)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	data->forks_sem = sem_open("forks_sem", O_CREAT, 0666, args->num_philos);
	data->print_sem = sem_open("print_sem", O_CREAT, 0666, 1);
}
