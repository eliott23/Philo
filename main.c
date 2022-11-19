#include "philo.h"

void	get_timestamp(int tv_start)
{
	struct timeval t;

	gettimeofday(&t,NULL);
	printf("%d ms since the start of the program\n",(t.tv_usec - tv_start) / 1000);
}

// void *get_timestamp(void *i)
// {
// 	printf("Hi am philosopher number %d\n", (*(int *)i) + 1);
// 	usleep(70);
// 	printf("Hi am philo %d and am dead\n", (*(int *)i) + 1);
// 	free(i);
// 	return(0);
// }

int	main(int ac, char **av)
{
	struct timeval start;
	gettimeofday(&start,NULL);
	printf("start time = %ld,%d\n",start.tv_sec, start.tv_usec);
	int	i = 0;
	int	*temp;
	usleep(900);
	if (ac < 5)
		return (0);
	int	n_philo = ft_atoi(av[1]);
	pthread_t *t = malloc(sizeof(pthread_t) * n_philo * 8000000);
	// while (i < n_philo)
	// {
	// 	temp = malloc(sizeof(int));
	// 	*temp = i;
	// 	pthread_create(&t[i],NULL, &get_timestamp, temp);
	// 	i++;
	// }
	// i = 0;
	// while (i < n_philo)
	// {
	// 	pthread_join(t[i],NULL);
	// 	i++;
	// }
	get_timestamp(start.tv_usec);
}