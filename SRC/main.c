/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:23:16 by clecat            #+#    #+#             */
/*   Updated: 2022/10/11 15:19:13 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

/*fonction autorisee : memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/

// routinephilo : manger, penser et dormir 
// philo pense en attendant de pouvoir manger
//faire la boucle et l'arreter des la premiere mort
void	*routine(void *arg)
{
	t_phil	*philo;

	philo = (t_phil *)arg;
	while (check_death(*philo) != 1 || philo->nb_time_eat
		<= philo->acs_tbl->nb_times_must_eat)
	{
		ft_eat(*philo);
		ft_sleep(*philo);
		ft_think(*philo);
		if (check_death(*philo) == 1)
			exit(0);
	}
	return (NULL);
}

/*timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died*/
//acces fork_left fait automatiquement avec lock
//affichage temp en ms avec init_ms
void	ft_eat(t_phil philo)
{
	int	ret;

	ret = pthread_mutex_lock(philo.fork);
	if (philo.nb_philo == philo.acs_tbl->nb_of_philo - 1)
		pthread_mutex_lock(philo.acs_tbl->p[0].fork);
	else
		pthread_mutex_lock(philo.acs_tbl->p[philo.nb_philo + 1].fork);
	pthread_mutex_lock(&philo.acs_tbl->print);
	printf("%lld %d has taken a fork\n",
		(init_ms() - philo.acs_tbl->time_day), philo.nb_philo);
	printf("%lld %d is eating\n",
		(init_ms() - philo.acs_tbl->time_day), philo.nb_philo);
	pthread_mutex_unlock(&philo.acs_tbl->print);
	philo.nb_time_eat += 1;
	ft_usleep(philo.acs_tbl->time_eat);
	philo.time_bfr_die = (philo.acs_tbl->time_die + (init_ms() - philo.acs_tbl->time_day));
	pthread_mutex_unlock(philo.fork);
	if (philo.nb_philo == philo.acs_tbl->nb_of_philo - 1)
		pthread_mutex_unlock(philo.acs_tbl->p[0].fork);
	else
		pthread_mutex_unlock(philo.acs_tbl->p[philo.nb_philo + 1].fork);
	if (check_death(philo) == 1)
		exit(0);
}

void	ft_sleep(t_phil philo)
{
	pthread_mutex_lock(&philo.acs_tbl->print);
	printf("%lld %d is sleeping\n", (init_ms() - philo.acs_tbl->time_day),
		philo.nb_philo);
	pthread_mutex_unlock(&philo.acs_tbl->print);
	ft_usleep(philo.acs_tbl->time_sleep);
}

//si le philo n'a fait qu'attendre car impossibilite de manger
//faire un check_death pour verifier si le philo meure pendant qu'il mange
//et en dehors aussi pour quand il attend
int	check_death(t_phil philo)
{
	printf("timebfrdie2 = %d, timeday = %lld\n", philo.time_bfr_die, (init_ms() - philo.acs_tbl->time_day));
	if ((philo.time_bfr_die + 10) < (init_ms() - philo.acs_tbl->time_day))
	{
		pthread_mutex_lock(&philo.acs_tbl->print);
		printf("%lld %d died\n", (init_ms() - philo.acs_tbl->time_day),
			philo.nb_philo);
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
	free(table.p->philo);
	return (0);
}
