/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:58:43 by houbeid           #+#    #+#             */
/*   Updated: 2021/11/03 09:32:56 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct s_g	*get_data(int argc, char **argv)
{
	struct s_g	*g;

	g = malloc(sizeof(struct s_g));
	pthread_mutex_init(&g->died, NULL);
	g->nb_of_eat = -1;
	g->nb_done = 0;
	g->nbr_of_philos = atoi(argv[1]);
	g->time_to_die = atoi(argv[2]);
	g->time_to_eat = atoi(argv[3]);
	g->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		g->nb_of_eat = atoi(argv[5]);
	return (g);
}

void	supervisor(t_philo *philos)
{
	int	i;

	while (philos->g->nb_done < philos->g->nbr_of_philos)
	{
		i = 0;
		while (i < philos->g->nbr_of_philos)
		{
			if (philos[i].iseating == 0
				&& (time_now() - philos[i].last_time_eat)
				 >= philos[i].g->time_to_die && !philos[i].is_done)
			{
				print(&philos[i], DIED);
				return ;
			}
			i++;
		}
	}
}

void	create_thread(t_philo *philos, struct s_g *g)
{
	int	i;

	i = 0;
	while (i < g->nbr_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].is_done = 0;
		philos[i].last_time_eat = time_now();
		philos[i].g = g;
		philos[i].iseating = 0;
		pthread_create(&philos[i].profil, NULL, routine_philos, &philos[i]);
		usleep(100);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	struct s_g	*g;
	int			i;

	if (check_erros(argv, argc))
	{
		write(2, "error\n", 6);
		return (1);
	}
	g = get_data(argc, argv);
	if (g->nbr_of_philos <= 0)
		return (0);
	philos = malloc(sizeof(t_philo) * g->nbr_of_philos);
	g->forks = malloc(sizeof(pthread_mutex_t) * g->nbr_of_philos);
	i = 0;
	while (i < g->nbr_of_philos)
	{
		pthread_mutex_init(&g->forks[i], NULL);
		i++;
	}
	create_thread(philos, g);
	supervisor(philos);
	return (0);
}
