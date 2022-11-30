/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:48:09 by aababach          #+#    #+#             */
/*   Updated: 2022/11/30 12:31:09 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	m_helper(t_inf temp, int i, int count)
{
	long long	l_meal;

	while (i < temp.n_philo)
	{
		pthread_mutex_lock(&(temp.death_mutex[i]));
		l_meal = temp.last_meal[i];
		if (temp.n_eat && temp.n_eat[i] >= temp.m_eat)
			count++;
		if (pthread_mutex_unlock(&(temp.death_mutex[i])))
			return (0);
		if ((get_timestamp(temp.start) - l_meal) >= temp.t_die)
		{
			m_helper2(temp, i);
			return (0);
		}
		i++;
		if (count == temp.n_philo)
			return (0);
		else if (i == temp.n_philo)
		{
			i = 0;
			count = 0;
		}
	}
	return (0);
}

void	ft_usleep(long long v, t_inf inf)
{
	long long	i;

	i = get_timestamp(inf.start);
	while (get_timestamp(inf.start) - i < v)
		usleep(250);
}

long long	get_timestamp(struct timeval start)
{
	struct timeval	t;
	long long		v;

	gettimeofday(&t, NULL);
	v = ((t.tv_sec * 1000000) \
			+ t.tv_usec - (start.tv_sec * 1000000) - start.tv_usec) / 1000;
	return (v);
}

static	void	h(t_inf *temp, int ac, char **av)
{
	int	i;

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

int	ft_init(t_inf *temp, char **av, int ac)
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
	if (!ft_p(temp, &i))
		return (0);
	while (i < temp->n_philo)
	{
		pthread_mutex_init(&(temp->mutex[i]), NULL);
		pthread_mutex_init(&(temp->death_mutex[i]), NULL);
		i++;
	}
	h(temp, ac, av);
	return (1);
}
