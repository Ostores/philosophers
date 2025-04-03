/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlinott <emlinott@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:18:03 by emlinott          #+#    #+#             */
/*   Updated: 2025/04/03 22:55:03 by emlinott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	join_monitor_thread(t_cardinal *c)
{
	pthread_join(c->monitor_thread, NULL);
}

//

void	join_philosophers_threads(t_cardinal *c, int i)
{
	while (--i >= 0)
		pthread_join(c->philos[i].thread, NULL);
}

int	create_philosophers_threads(t_cardinal *c)
{
	int	i;

	i = 0;
	while (i < c->philo_count)
	{
		if (pthread_create(&c->philos[i].thread, NULL,
				philo_life, &c->philos[i]) != 0)
		{
			set_stop(c, true);
			join_philosophers_threads(c, i);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	create_monitor_thread(t_cardinal *c)
{
	if (pthread_create(&c->monitor_thread, NULL, monitor, c) != 0)
	{
		set_stop(c, true);
		join_philosophers_threads(c, c->philo_count);
		return (ERROR);
	}
	return (SUCCESS);
}

//

int	philo_start(t_cardinal *c)
{
	if (create_philosophers_threads(c) == ERROR)
		return (ERROR);
	if (create_monitor_thread(c) == ERROR)
		return (ERROR);
	join_philosophers_threads(c, c->philo_count);
	join_monitor_thread(c);
	return (SUCCESS);
}
