/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlinott <emlinott@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 22:42:16 by emlinott          #+#    #+#             */
/*   Updated: 2025/04/03 23:27:06 by emlinott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static char	*select_color(char *msg)
{
	if (strstr(msg, "eating"))
		return ("\033[1;32m");
	else if (strstr(msg, "sleeping"))
		return ("\033[1;34m");
	else if (strstr(msg, "thinking"))
		return ("\033[1;33m");
	else if (strstr(msg, "taken"))
		return ("\033[1;35m");
	else if (strstr(msg, "died"))
		return ("\033[1;31m");
	return ("");
}

static char	*select_icon(char *msg)
{
	if (strstr(msg, "eating"))
		return ("🍴 ");
	else if (strstr(msg, "sleeping"))
		return ("💤 ");
	else if (strstr(msg, "thinking"))
		return ("💭 ");
	else if (strstr(msg, "taken"))
		return ("⇆ ");
	else if (strstr(msg, "died"))
		return ("💀 ");
	return ("");
}

static void	print_formatted_time(void)
{
	long long	ms;
	long		hours;
	long		minutes;
	long		seconds;
	long		millis;

	ms = get_current_time();
	hours = (ms / 3600000) % 24;
	minutes = (ms / 60000) % 60;
	seconds = (ms / 1000) % 60;
	millis = ms % 1000;
	printf("\n┌─[🕒 %02ld:%02ld:%02ld.%03ld]─", hours, minutes, seconds, millis);
}

void	print_status(t_philo *philo, t_cardinal *c, char *msg)
{
	const char	*color;
	const char	*icon;
	const char	*reset;

	color = select_color(msg);
	icon = select_icon(msg);
	reset = "\033[0m";
	pthread_mutex_lock(&c->print_mutex);
	if (!c->stop)
	{
		print_formatted_time();
		printf("\n│ Philosopher \033[1;37m%d\033[0m %s%s%s%s",
			philo->id, color, icon, msg, reset);
		printf("\n└─────────────────────────────\n");
	}
	pthread_mutex_unlock(&c->print_mutex);
}

//fflush(stdout);

// void	print_status(t_philo *philo, t_cardinal *c, char *msg)
// {
// 	pthread_mutex_lock(&c->print_mutex);
// 	if (!c->stop)
// 	{
// 		printf("%lld %d %s\n", get_current_time(), philo->id, msg);
// 	}
// 	pthread_mutex_unlock(&c->print_mutex);
// }
