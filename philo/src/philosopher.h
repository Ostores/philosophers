/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlinott <emlinott@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:27:49 by emlinott          #+#    #+#             */
/*   Updated: 2025/04/03 23:20:03 by emlinott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define MAX_PHILOS 200
# define SUCCESS 0
# define ERROR 1

# define COLOR_RED     "\033[1;31m"
# define COLOR_GREEN   "\033[1;32m"
# define COLOR_YELLOW  "\033[1;33m"
# define COLOR_BLUE    "\033[1;34m"
# define COLOR_MAGENTA "\033[1;35m"
# define COLOR_CYAN    "\033[1;36m"
# define COLOR_WHITE   "\033[1;37m"
# define COLOR_RESET   "\033[0m"

/* Icônes */
# define ICON_EAT    "🍴 "
# define ICON_SLEEP  "💤 "
# define ICON_THINK  "💭 "
# define ICON_FORK   "⇆ "
# define ICON_DEAD   "💀 "
# define ICON_CLOCK  "🕒 "

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long long			last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_lock;
	pthread_t			thread;
	struct s_cardinal	*cardinal;
}	t_philo;

typedef struct s_cardinal
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_goal;
	bool			stop;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	*forks;

	t_philo			*philos;
	pthread_t		monitor_thread;
}	t_cardinal;

// utils
long long	get_current_time(void);
void		print_status(t_philo *philo, t_cardinal *c, char *msg);
bool		should_stop(t_cardinal *c);
void		set_stop(t_cardinal *c, bool value);

// main
int			init_data(t_cardinal *c, char **av, int ac);
int			philo_start(t_cardinal *c);
void		clean_up(t_cardinal *c);

// cardinal
void		*philo_life(void *arg);
void		*monitor(void *arg);

// action
void		take_forks(t_philo *philo, t_cardinal *c);
void		release_forks(t_philo *philo);
void		philo_eat(t_philo *philo, t_cardinal *c);
void		philo_sleep(t_philo *philo, t_cardinal *c);
void		philo_think(t_philo *philo, t_cardinal *c);

// utils
long long	get_current_time(void);
void		print_status(t_philo *philo, t_cardinal *c, char *msg);
bool		should_stop(t_cardinal *c);
void		set_stop(t_cardinal *c, bool value);
long		ft_atol(const char *str);

#endif