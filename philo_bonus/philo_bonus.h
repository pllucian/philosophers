/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 10:36:11 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/26 11:06:43 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

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
	t_args	*args;
	pid_t	*philos;
	sem_t	*forks_sem;
	sem_t	*print_sem;
	long	start_time;
}		t_data;

typedef struct s_philo
{
	int			num;
	long		time_last_eat;
	int			num_eats;
	t_data		*data;
}		t_philo;

int		ft_atoi(const char *nptr);
int		ft_strisdigit(const char *str);
size_t	ft_strlen(const char *str);

void	kill_pids(t_data *data);
void	end_sems(t_data *data);
void	init_sems(t_data *data, t_args *args);

void	print_status(t_philo *philo, char *status);
void	print_died(t_philo *philo);
long	get_time(void);
void	free_all(t_philo *philos, t_data *data);
int		exit_error(char *str);

void	philo_put_forks(t_philo *philo);
void	philo_take_forks(t_philo *philo);
void	*simulation(void *arg);
int		philo_process(t_philo *philo);

int		end_philos(t_data *data);
int		init_philos(t_philo *philos, t_data *data);
int		init_data(t_data *data, t_args *args, t_philo **philos);
int		init_args(t_args *args, int argc, char **argv);

#endif
