#include <unistd.h>
#include <stdio.h>

int	main()
{
	int pid = fork();
	char *str = (pid == 0 ? "child" : "parent");
	printf("%s proccess started\n", str);
	sleep(2);
	printf("%s proccess ended\n",str);
}
