/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:12:53 by houbeid           #+#    #+#             */
/*   Updated: 2021/11/02 18:24:30 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
	struct timeval	current_time;
	long			time_mili;

	gettimeofday(&current_time, NULL);
	time_mili = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time_mili);
}

void	ft_sleep(unsigned long us)
{
	unsigned long	begin;

	begin = time_now() * 1000;
	usleep(us - 20000);
	while ((time_now() * 1000) - begin < us)
		;
}

void	print(t_philo *philos, enum e_status stat)
{
	pthread_mutex_lock(&philos->g->died);
	if (stat == THINKING)
		printf("%lu %d is thinking\n", time_now(), philos->id);
	else if (stat == TAKE_FORK)
		printf("%lu %d has taken a fork\n", time_now(), philos->id);
	else if (stat == EATING)
		printf("%lu %d is eating\n", time_now(), philos->id);
	else if (stat == SLEEPING)
		printf("%lu %d is sleeping\n", time_now(), philos->id);
	else if (stat == DIED)
	{
		printf("%lu %d is died\n", time_now(), philos->id);
		return ;
	}
	pthread_mutex_unlock(&philos->g->died);
}

void	eat(t_philo *philos, int id)
{
	pthread_mutex_lock(&philos->g->forks[id - 1]);
	print(philos, TAKE_FORK);
	pthread_mutex_lock(&philos->g->forks[id % philos->g->nbr_of_philos]);
	print(philos, TAKE_FORK);
	philos->iseating = 1;
	print(philos, EATING);
	philos->last_time_eat = time_now();
}

void	*routine_philos(void *arg)
{
	int		id;
	int		count_eat;
	t_philo	*philos;

	philos = (t_philo *)arg;
	id = philos->id;
	count_eat = 0;
	while (philos->g->nb_of_eat == -1 || count_eat != philos->g->nb_of_eat)
	{
		eat(philos, id);
		count_eat++;
		ft_sleep(philos->g->time_to_eat * 1000);
		philos->iseating = 0;
		pthread_mutex_unlock(&philos->g->forks[id - 1]);
		pthread_mutex_unlock(&philos->g->forks[id % philos->g->nbr_of_philos]);
		print(philos, SLEEPING);
		ft_sleep(philos->g->time_to_sleep * 1000);
		print(philos, THINKING);
	}
	philos->is_done = 1;
	philos->g->nb_done++;
	return (NULL);
}
