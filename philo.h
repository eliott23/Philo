#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct var{
	int				*d_flag;
	int				i;
	int				my_frk;
	int				othr_frk;
	struct timeval	start;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*death_mutex;
	long long		*last_meal;
	int				t_sleep;
	int				t_eat;
	int				t_die;
	int				n_philo;
	int				*n_eat;
	int				m_eat;
}t_inf;

long long int   ft_atoi(const char *str);
void			ft_init(t_inf *temp, char **av, int ac);
long long		get_timestamp(struct timeval start);
#endif
