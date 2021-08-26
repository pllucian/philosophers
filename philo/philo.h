/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 10:36:11 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/25 14:58:24 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int		num_philos;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		num_eats;
}		t_args;

typedef struct s_data
{
	t_args			*args;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	print_mutex;
	long			start_time;
	int				philos_eated;
}		t_data;

typedef struct s_philo
{
	int		num;
	long	time_last_eat;
	int		num_eats;
	t_data	*data;
}		t_philo;

int		ft_atoi(const char *nptr);
int		ft_strisdigit(const char *str);
size_t	ft_strlen(const char *str);

void	print_status(t_philo *philo, char *status);
void	print_died(t_philo *philo);
long	get_time(void);
void	free_all(t_philo *philos, t_data *data);
int		exit_error(char *str);

void	philo_put_forks(t_philo *philo);
int		philo_take_forks(t_philo *philo);
void	*simulation(void *arg);
void	*monitor(void *arg);

int		end_philos(t_data *data);
int		init_philos(t_philo *philos, t_data *data);
int		init_data(t_data *data, t_args *args, t_philo **philos);
int		init_args(t_args *args, int argc, char **argv);

#endif
