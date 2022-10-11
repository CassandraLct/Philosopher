/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:30:08 by clecat            #+#    #+#             */
/*   Updated: 2022/10/11 13:47:24 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"
// 3 fonctions

int	check_arg(int argc, char **argv)
{
	if (argc == 1)
		printf("Error -> no arg\n");
	if (argc < 5)
		printf("Missing arguments\n");
	else if (argc > 6)
		printf("Too much arguments\n");
	else
	{
		if (check_digit(argv) == 1)
			return (1);
	}
	return (0);
}

// nb_of_philo ; time_die; time_eat ; time_sleep
int	init_struct(t_t *table, char **argv)
{
	table->nb_of_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->nb_times_must_eat = ft_atoi(argv[5]);
	table->nb_of_fork = table->nb_of_philo;
	table->time_day = init_ms();
	table->p = malloc(sizeof(t_phil) * table->nb_of_philo);
	pthread_mutex_init(&table->print, NULL);
	init_philo(table);
	return (0);
}

int	init_philo(t_t *table)
{
	int	i;

	i = 0;
	while (i < table->nb_of_philo)
	{
		table->p[i].acs_tbl = table;
		table->p[i].nb_philo = i;
		table->p[i].nb_time_eat = 0;
		table->p[i].time_bfr_die = table->time_die;
		table->p[i].fork = malloc(sizeof(pthread_mutex_t));
		table->p[i].fork_left = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(table->p[i].fork, NULL);
		pthread_create(&table->p[i].philo, NULL, &routine, &table->p[i]);
		i++;
		pthread_detach(table->p[i].philo);
	}
	i = 0;
	while (i < table->nb_of_philo)
	{
		if (pthread_join(table->p[i].philo, NULL) != 0)
			return (2);
		i++;
	}
	return (0);
}

void	ft_think(t_phil philo)
{
	pthread_mutex_lock(&philo.acs_tbl->print);
	printf("%lld %d is thinking\n",
		(init_ms() - philo.acs_tbl->time_day), philo.nb_philo);
	pthread_mutex_unlock(&philo.acs_tbl->print);
}
