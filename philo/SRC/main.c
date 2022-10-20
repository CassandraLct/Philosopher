/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:23:16 by clecat            #+#    #+#             */
/*   Updated: 2022/10/20 13:36:35 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

/*autorisee: memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/
void	*routine(void *arg)
{
	t_phil	*philo;
	int		ret;

	usleep(500);
	philo = (t_phil *)arg;
	if ((philo->nb_philo % 2) == 1)
		usleep(200);
	while (1)
	{
		ret = ft_eat(*philo);
		philo->timebfrdie = ret;
		ft_sleep(*philo);
		ft_usleep(0);
		if (check_death(*philo) == 1)
			exit(0);
		ft_think(*philo);
		if (check_death(*philo) == 1)
			exit(0);
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
	ft_usleep(ph.acs_tbl->time_eat);
	ph.timebfrdie = (ph.acs_tbl->time_die + (init_ms() - ph.acs_tbl->time_day));
	if (check_death(ph) == 1)
		exit (0);
	pthread_mutex_unlock(ph.fork);
	if (ph.nb_philo == ph.acs_tbl->nb_of_philo - 1)
		pthread_mutex_unlock(ph.acs_tbl->p[0].fork);
	else
		pthread_mutex_unlock(ph.acs_tbl->p[ph.nb_philo + 1].fork);
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
	if ((philo.timebfrdie) < (init_ms() - philo.acs_tbl->time_day)
		&& philo.acs_tbl->philo_died != 1)
	{
		philo.acs_tbl->philo_died = 1;
		pthread_mutex_lock(&philo.acs_tbl->print);
		printf("%lld %d died\n", ((init_ms() - philo.acs_tbl->time_day)),
			philo.nb_philo + 1);
		return (1);
	}
	if (philo.acs_tbl->philo_died == 1)
		return (1);
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

//dernier soucis a regler: le dernier thinking ne s'affiche pas!