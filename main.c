/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:41:30 by aababach          #+#    #+#             */
/*   Updated: 2022/11/26 18:34:42 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	helper3(t_inf l_inf)
{
	pthread_mutex_lock(&(l_inf.mutex[l_inf.my_frk]));
	pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
	printf("%lld %d has taken his fork\n", \
	get_timestamp(l_inf.start), l_inf.i);
	pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
	pthread_mutex_lock(&(l_inf.mutex[l_inf.othr_frk]));
	pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
	printf("%lld %d has taken the other fork\n", \
	get_timestamp(l_inf.start), l_inf.i);
	pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
	pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
	printf("%lld %d is eating\n", \
	get_timestamp(l_inf.start), l_inf.i);
	if (l_inf.n_eat)
	l_inf.n_eat[l_inf.i - 1]++;
	pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
	ft_usleep(l_inf.t_eat, l_inf);
	pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
	l_inf.last_meal[l_inf.i - 1] = get_timestamp(l_inf.start);
	pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
	pthread_mutex_unlock(&(l_inf.mutex[l_inf.my_frk]));
	pthread_mutex_unlock(&(l_inf.mutex[l_inf.othr_frk]));
	pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
	printf("%lld %d is sleeping\n", \
	get_timestamp(l_inf.start), l_inf.i);
}

void	helper(t_inf l_inf)
{	
	pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
	printf("%lld %d is thinking\n", \
	get_timestamp(l_inf.start), l_inf.i);
	pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
}

int	helper2(t_inf l_inf)
{
	if (l_inf.n_philo == 1)
	{
		ft_usleep(l_inf.t_die, l_inf);
		*(l_inf.d_flag) = l_inf.i;
		return (0);
	}
	return (1);
}

void	*rout(void *inf)
{
	t_inf	l_inf;

	l_inf = *(t_inf *)inf;
	l_inf.my_frk = l_inf.i - 1;
	if (l_inf.i >= 2)
		l_inf.othr_frk = l_inf.i - 2;
	else
		l_inf.othr_frk = l_inf.n_philo - 1;
	if (!(l_inf.i % 2))
		ft_usleep(1, l_inf);
	pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
	if (l_inf.n_eat)
		l_inf.n_eat[l_inf.i -1] = 0;
	pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
	while (1)
	{
		helper(l_inf);
		if (!helper2(l_inf))
			return (0);
		helper3(l_inf);
		pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
		ft_usleep(l_inf.t_sleep, l_inf);
	}
}

void	m_helper2(t_inf temp, int i)
{	
	while (temp.n_philo)
	{
		pthread_mutex_lock(&(temp.death_mutex[temp.n_philo - 1]));
		(temp.n_philo)--;
	}
	printf("%lld %d died\n", \
	get_timestamp(temp.start), i + 1);
}

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
			//m_helper2(temp, i);
			while (temp.n_philo)
			{
				pthread_mutex_lock(&(temp.death_mutex[temp.n_philo - 1]));
				(temp.n_philo)--;
			}
			printf("%lld %d died\n", \
			get_timestamp(temp.start), i + 1);
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

int	main(int ac, char **av)
{
	t_inf		*inf;
	t_inf		temp;
	pthread_t	*t;
	int			i;
	int			count;

	count = 0;
	i = 0;
	if (ac < 5)
		return (0);
	ft_init(&temp, av, ac);
	t = malloc(sizeof(pthread_t) * temp.n_philo);
	while (i < temp.n_philo)
	{
		inf = malloc(sizeof(t_inf));
		*inf = temp;
		inf->i = i + 1;
		if (pthread_create(&t[i], NULL, &rout, inf))
			return (0);
		i++;
	}
	if (!(m_helper(temp, 0, count)))
		return (0);
}
