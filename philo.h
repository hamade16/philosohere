/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:49:03 by houbeid           #+#    #+#             */
/*   Updated: 2021/11/02 18:30:53 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

struct	s_g {
	int				nbr_of_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nb_of_eat;
	pthread_mutex_t	*forks;
	int				nb_done;
	pthread_mutex_t	died;
};

typedef struct g_philo
{
	int			id;
	pthread_t	profil;
	int			is_done;
	int			iseating;
	long		last_time_eat;
	struct s_g	*g;
}				t_philo;

enum	e_status{
	THINKING,
	TAKE_FORK,
	EATING,
	SLEEPING,
	DIED
};

long		time_now(void);
void		ft_sleep(unsigned long us);
void		print(t_philo *philos, enum e_status stat);
void		*routine_philos(void *arg);
struct s_g	*get_data(int argc, char **argv);
void		supervisor(t_philo *philos);
void		create_thread(t_philo *philos, struct s_g *g);
int			check_erros(char *av[], int ac);
int			t_isdigit(char number);
void		eat(t_philo *philos, int id);

#endif