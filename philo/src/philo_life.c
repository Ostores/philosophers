/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlinott <emlinott@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:21:05 by emlinott          #+#    #+#             */
/*   Updated: 2025/04/03 23:58:32 by emlinott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_life(void *arg)
{
	t_philo		*philo;
	t_cardinal	*c;

	philo = (t_philo *)arg;
	c = philo->cardinal;
	while (!should_stop(c))
	{
		take_forks(philo, c);
		philo_eat(philo, c);
		drop_forks(philo);
		if (c->meals_goal > 0 && philo->meals_eaten >= c->meals_goal)
			break ;
		philo_sleep(philo, c);
		philo_think(philo, c);
	}
	return (NULL);
}
