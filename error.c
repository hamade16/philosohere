/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:17:44 by houbeid           #+#    #+#             */
/*   Updated: 2021/11/02 11:38:44 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	t_isdigit(char number)
{
	if ((number >= '0' && number <= '9'))
	{
		return (1);
	}
	else
		return (0);
}

int	check_erros(char *av[], int ac)
{
	int	i;
	int	j;

	if (ac == 5 || ac == 6)
		;
	else
		return (1);
	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		if (av[i][j] == '\0' || av[i][j] == '-')
			return (1);
		while (av[i][j])
		{
			if (t_isdigit(av[i][j]) != 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
