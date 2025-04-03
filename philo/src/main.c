/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlinott <emlinott@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:14:17 by emlinott          #+#    #+#             */
/*   Updated: 2025/04/03 23:18:52 by emlinott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	clean_up(t_cardinal *c)
{
	int	i;

	if (c->forks)
	{
		i = 0;
		while (i < c->philo_count)
		{
			pthread_mutex_destroy(&c->forks[i]);
			i++;
		}
		free(c->forks);
	}
	if (c->philos)
	{
		i = 0;
		while (i < c->philo_count)
		{
			pthread_mutex_destroy(&c->philos[i].meal_lock);
			i++;
		}
		free(c->philos);
	}
	pthread_mutex_destroy(&c->print_mutex);
	pthread_mutex_destroy(&c->stop_mutex);
}

int	main(int ac, char **av)
{
	t_cardinal	c;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die"
			" time_to_eat time_to_sleep [meals_goal]\n", av[0]);
		return (ERROR);
	}
	if (init_data(&c, av, ac) != SUCCESS)
		return (ERROR);
	if (philo_start(&c) != SUCCESS)
	{
		clean_up(&c);
		return (ERROR);
	}
	clean_up(&c);
	return (SUCCESS);
}
