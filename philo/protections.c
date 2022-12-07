/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:51:25 by aababach          #+#    #+#             */
/*   Updated: 2022/12/07 15:26:45 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_f(t_inf *inf)
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
	return (1);
}

int	ft_p(t_inf *inf, int *i)
{
	*i = 0;
	if (inf->n_philo <= 0 || inf->t_die <= 0 || \
			inf->t_eat <= 0 || inf->t_sleep <= 0 || \
			(inf->n_eat && inf->m_eat <= 0))
		return (0);
	if (!(inf->n_eat) && !(inf->mutex) && \
			!(inf->death_mutex) && !(inf->last_meal) && !(inf->d_flag))
		return (0);
	return (1);
}

void	ft_h(t_inf temp, int i)
{
	pthread_mutex_unlock(&(temp.death_mutex[i]));
	m_helper2(temp, i);
}
