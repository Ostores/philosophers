/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlinott <emlinott@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:45:33 by emlinott          #+#    #+#             */
/*   Updated: 2025/04/03 23:17:27 by emlinott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_atol(const char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -sign;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if ((result * sign) > LONG_MAX)
			return (LONG_MAX);
		if ((result * sign) < LONG_MIN)
			return (LONG_MIN);
		i++;
	}
	return (result * sign);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	should_stop(t_cardinal *c)
{
	bool	stop;

	pthread_mutex_lock(&c->stop_mutex);
	stop = c->stop;
	pthread_mutex_unlock(&c->stop_mutex);
	return (stop);
}

void	set_stop(t_cardinal *c, bool value)
{
	pthread_mutex_lock(&c->stop_mutex);
	c->stop = value;
	pthread_mutex_unlock(&c->stop_mutex);
}
