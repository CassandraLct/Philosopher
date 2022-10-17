/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:23:16 by clecat            #+#    #+#             */
/*   Updated: 2022/10/17 14:12:49 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

//chose a faire : regler soucis philo 1 et d'affichage,
//recherche bonus ; usleep(200);
/*autorisee: memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/
void	*routine(void *arg)
{
	t_phil	*philo;
	int		ret;

	philo = (t_phil *)arg;
	if ((philo->nb_philo % 2) != 0)
		usleep(200);
	while (1)
	{
		if (check_death(*philo) == 1)
			exit(0);
		ret = ft_eat(*philo);
		philo->timebfrdie += ret;
		//printf("test0 %d\n", philo->nb_philo);
		if (check_death(*philo) == 1)
			exit(0);
		//printf("test01 %d\n", philo->nb_philo);
		ft_sleep(*philo);
		//printf("test1 %d\n", philo->nb_philo);
		if (check_death(*philo) == 1)
			exit(0);
		//printf("test2 %d\n", philo->nb_philo);
		ft_think(*philo);
		if (check_death(*philo) == 1)
			exit(0);
		//printf("test3 %d\n", philo->nb_philo);
		philo->nb_time_eat++;
		if (philo->nb_time_eat == philo->acs_tbl->nb_times_must_eat)
			exit(0);
	}
	return (NULL);
}

int	ft_eat(t_phil ph)
{
	pthread_mutex_lock(ph.fork);
	if (ph.nb_philo == ph.acs_tbl->nb_of_philo - 1)
		pthread_mutex_lock(ph.acs_tbl->p[0].fork);
	else
		pthread_mutex_lock(ph.acs_tbl->p[ph.nb_philo + 1].fork);
	pthread_mutex_lock(&ph.acs_tbl->print);
	printf("%lld %d has taken a fork\n",
		(init_ms() - ph.acs_tbl->time_day), ph.nb_philo + 1);
	printf("%lld %d is eating\n",
		(init_ms() - ph.acs_tbl->time_day), ph.nb_philo + 1);
	pthread_mutex_unlock(&ph.acs_tbl->print);
	//ph.nb_time_eat += 1;
	//printf(" oui %d\n", ph.nb_philo);
	ft_usleep(ph.acs_tbl->time_eat);
	//printf("test1111%d\n", ph.nb_philo);
	if (check_death(ph) == 1)
		exit(0);
	//printf("tes22222%d\n", ph.nb_philo);
	ph.timebfrdie = (ph.acs_tbl->time_die + (init_ms() - ph.acs_tbl->time_day));
	pthread_mutex_unlock(ph.fork);
	//printf("tes33333%d\n", ph.nb_philo);
	if (ph.nb_philo == ph.acs_tbl->nb_of_philo - 1)
		pthread_mutex_unlock(ph.acs_tbl->p[0].fork);
	else
		pthread_mutex_unlock(ph.acs_tbl->p[ph.nb_philo + 1].fork);
	if (check_death(ph) == 1)
		exit(0);
	//printf("tes4444444 %d\n", ph.nb_philo);
	return (ph.timebfrdie);
}

void	ft_sleep(t_phil philo)
{
	pthread_mutex_lock(&philo.acs_tbl->print);
	printf("%lld %d is sleeping\n", (init_ms() - philo.acs_tbl->time_day),
		philo.nb_philo + 1);
	pthread_mutex_unlock(&philo.acs_tbl->print);
	ft_usleep(philo.acs_tbl->time_sleep);
}

int	check_death(t_phil philo)
{
	if ((philo.timebfrdie) < (init_ms() - philo.acs_tbl->time_day))
	{
		pthread_mutex_lock(&philo.acs_tbl->print);
		printf("%lld %d died\n", ((init_ms() - philo.acs_tbl->time_day)),
			philo.nb_philo + 1);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_t	table;

	if (check_arg(argc, argv) == 1)
		return (1);
	init_struct(&table, argv);
	free_philo(table);
	return (0);
}

// pour philo 2 400 150 300 : 2 doit mourir