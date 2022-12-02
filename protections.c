/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:51:25 by aababach          #+#    #+#             */
/*   Updated: 2022/12/02 13:43:12 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_f(t_inf *inf)
{
	int	i;

	i = 0;
	if (inf->n_eat)
	{
		while (i < inf->n_philo)
		{
			inf->n_eat[i] = 0;
			i++;
		}
	}
}

int	ft_p(t_inf *inf, int *i)
{
	*i = 0;
	if (inf->n_philo <= 0 || inf->t_die <= 0 || \
			inf->t_eat <= 0 || inf->t_sleep <= 0)
		return (0);
	if (!(inf->n_eat) && !(inf->mutex) && \
			!(inf->death_mutex) && !(inf->last_meal) && !(inf->d_flag))
		return (0);
	return (1);
}
