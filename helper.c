/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:48:09 by aababach          #+#    #+#             */
/*   Updated: 2022/11/26 17:48:11 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_inf *temp, char **av, int ac)
{
	int	i;

	i = 0;
	gettimeofday(&(temp->start), NULL);
	temp->i = 0;
	temp->n_philo = ft_atoi(av[1]);
	temp->t_die = ft_atoi(av[2]);
	temp->t_eat = ft_atoi(av[3]);
	temp->t_sleep = ft_atoi(av[4]);
	temp->n_eat = malloc(sizeof(int) * (temp->n_philo));
	temp->mutex = malloc(sizeof(pthread_mutex_t) * (temp->n_philo));
	temp->death_mutex = malloc(sizeof(pthread_mutex_t) * (temp->n_philo));
	temp->last_meal = malloc(sizeof(long long) * (temp->n_philo));
	temp->d_flag = malloc(sizeof(int));
	*(temp->d_flag) = 0;
	i = 0;
	while (i < temp->n_philo)
	{
		pthread_mutex_init(&(temp->mutex[i]), NULL);
		pthread_mutex_init(&(temp->death_mutex[i]), NULL);
		i++;
	}
	i = 0;
	while (i < temp->n_philo)
	{
		temp->last_meal[i] = 0;
		i++;
	}
	if (ac > 5)
		temp->m_eat = ft_atoi(av[5]);
	else
		temp->n_eat = NULL;
}
