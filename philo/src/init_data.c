/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlinott <emlinott@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:25:18 by emlinott          #+#    #+#             */
/*   Updated: 2025/04/03 23:18:01 by emlinott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_philos_data(t_cardinal *c)
{
	int	i;

	i = 0;
	while (i < c->philo_count)
	{
		pthread_mutex_init(&c->forks[i], NULL);
		c->philos[i].id = i + 1;
		c->philos[i].meals_eaten = 0;
		c->philos[i].last_meal = get_current_time();
		c->philos[i].left_fork = &c->forks[i];
		c->philos[i].right_fork = &c->forks[(i + 1) % c->philo_count];
		pthread_mutex_init(&c->philos[i].meal_lock, NULL);
		c->philos[i].cardinal = c;
		i++;
	}
	pthread_mutex_init(&c->print_mutex, NULL);
	pthread_mutex_init(&c->stop_mutex, NULL);
}

static int	allocate_memory(t_cardinal *c)
{
	c->forks = malloc(sizeof(pthread_mutex_t) * c->philo_count);
	c->philos = malloc(sizeof(t_philo) * c->philo_count);
	if (!c->forks || !c->philos)
	{
		printf("Memory allocation failed\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	init_data(t_cardinal *c, char **av, int ac)
{
	c->philo_count = ft_atol(av[1]);
	c->time_to_die = ft_atol(av[2]);
	c->time_to_eat = ft_atol(av[3]);
	c->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		c->meals_goal = ft_atol(av[5]);
	else
		c->meals_goal = -1;
	c->stop = false;
	if (c->philo_count <= 0 || c->philo_count > MAX_PHILOS
		|| c->time_to_die <= 0 || c->time_to_eat <= 0
		|| c->time_to_sleep <= 0 || (ac == 6 && c->meals_goal <= 0))
	{
		printf("Invalid arguments\n");
		return (ERROR);
	}
	if (allocate_memory(c) != SUCCESS)
		return (ERROR);
	init_philos_data(c);
	return (SUCCESS);
}
