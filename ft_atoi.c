static void	ft_skip_signe(int *i, const char *str, int *s)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*(s) *= -1;
		(*i)++;
	}
}

long long int	ft_atoi(const char *str)
{
	int				i;
	int				s;
	long long int	rslt;

	rslt = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	ft_skip_signe (&i, str, &s);
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = rslt * 10 + str[i] - 48;
		i++;
	}
	return (rslt * s);
}