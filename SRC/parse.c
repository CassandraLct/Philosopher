/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:30:08 by clecat            #+#    #+#             */
/*   Updated: 2022/10/04 16:21:29 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

//check que des digit et que 5 ou 6 arg
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_digit(char **argv)
{
	int i;
	int j;
	
	i = 1;
	j = 0;
	while(argv[i] != '\0')
	{
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return(1);
			j++;
		}
		j = 0;
		i++;
	}
	return(0);
}

void	check_arg(int argc, char **argv)
{
	int i = 1;
	if (argc == 1)
		printf("Error -> no arg\n");
	if (argc < 5)
		write(1, "Missing arguments\n", 18);
	else if (argc > 6)
		write(1, "Too much arguments\n", 19);
	else
	{
		while(i != argc)
		{
			//printf("i = %d\n", i);
			if(check_digit(&argv[i]) == 1)
				printf("argv[%d] is not a digit\n", i);
			i++;
		}
	}
}

//init fork left
void fork_init(t_t table)
{
	int i;

	i = 0;
	while(i < table.nb_of_philo)
	{
		if (i == table.nb_of_philo - 1)
			table.p[i].fork_left = table.p[0].fork;
		else
			table.p[i].fork_left = table.p[i + 1].fork;
		i++;
	}
}

// nb_of_philo ; time_to_die; time_to_eat ; time_to_sleep
void init_struct(t_t *table, char **argv)
{
	table->nb_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->nb_of_fork = table->nb_of_philo;
	printf("nb-philo = %d, nb-fork = %d\n", table->nb_of_philo, table->nb_of_fork);
	printf("timedie = %d, timeeat = %d, timesleep = %d\n", table->time_to_die, table->time_to_eat, table->time_to_sleep);
	table->p = malloc(sizeof(t_phil) * table->nb_of_philo);
}