/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlinott <emlinott@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:21:58 by emlinott          #+#    #+#             */
/*   Updated: 2025/04/03 23:55:05 by emlinott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	philo_died(t_philo *philo, t_cardinal *c)
{
	long long	time_since_last_meal;

	pthread_mutex_lock(&philo->meal_lock);
	time_since_last_meal = get_current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	return (time_since_last_meal > c->time_to_die);
}

bool	all_philos_ate(t_cardinal *c)
{
	int	full_philos;
	int	i;

	full_philos = 0;
	if (c->meals_goal <= 0)
		return (false);
	i = 0;
	while (i < c->philo_count)
	{
		pthread_mutex_lock(&c->philos[i].meal_lock);
		if (c->philos[i].meals_eaten >= c->meals_goal)
			full_philos++;
		pthread_mutex_unlock(&c->philos[i].meal_lock);
		i++;
	}
	return (full_philos == c->philo_count);
}

static void	check_philosophers(t_cardinal *c)
{
	int	i;

	i = 0;
	while (i < c->philo_count)
	{
		if (philo_died(&c->philos[i], c))
		{
			print_status(&c->philos[i], c, "died");
			set_stop(c, true);
			return ;
		}
		i++;
	}
}

void	*monitor(void *arg)
{
	t_cardinal	*c;

	c = (t_cardinal *)arg;
	while (!should_stop(c))
	{
		usleep(1000);
		check_philosophers(c);
		if (all_philos_ate(c))
		{
			set_stop(c, true);
			break ;
		}
	}
	if (c->philo_count == 1)
		pthread_mutex_unlock(c->philos[0].left_fork);
	return (NULL);
}
