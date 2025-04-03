/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlinott <emlinott@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:35:41 by emlinott          #+#    #+#             */
/*   Updated: 2025/04/03 22:58:34 by emlinott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philo *philo, t_cardinal *c)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, c, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, c, "has taken right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, c, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, c, "has taken left fork");
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo, t_cardinal *c)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, c, "is eating");
	usleep(c->time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo, t_cardinal *c)
{
	print_status(philo, c, "is sleeping");
	usleep(c->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo, t_cardinal *c)
{
	print_status(philo, c, "is thinking");
}
