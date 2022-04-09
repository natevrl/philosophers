#include "../philo.h"

// check if : 
// --------> args are valid numbers
// --------> args are digit
// --------> no int overflow
// --------> no empty args ""
int error_handling(int ac, char **av)
{
	int i;

	if (ac != 5 && ac != 6)
		return (printf("Invalid params : ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [max_eat]\n"), 0);
	while (--ac)
	{
		if (av[ac][0] == '\0' || av[ac][0] == '0')
			return (printf("Empty arg(s) or 0 spotted\n"), 0);
		if (atl(av[ac]) > 2147483647 || atl(av[ac]) < -2147483648 || ft_strlen(av[ac]) > 12)
			return (printf("Please retry with valid int\n"), 0);
		i = -1;
		while (av[ac][++i])
			if (av[ac][i] < '0' || av[ac][i] > '9')
				return (printf("Non-digit arg(s) spotted"), 0);
	}
	return (1);
}
