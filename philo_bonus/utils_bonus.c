/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 10:59:12 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/25 17:11:01 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int					sign;
	unsigned long long	nbr;

	sign = 1;
	nbr = 0;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v' \
	|| *nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while ('0' <= *nptr && *nptr <= '9')
		nbr = nbr * 10 + *nptr++ - '0';
	if (sign == 1 && nbr > 2147483647)
		return (-1);
	if (sign == -1 && nbr > 2147483648)
		return (0);
	return ((int)nbr * sign);
}

int	ft_strisdigit(const char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (1);
		str++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t		len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}
