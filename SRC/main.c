/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:23:16 by clecat            #+#    #+#             */
/*   Updated: 2022/10/10 16:13:23 by clecat           ###   ########.fr       */
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
void	*routine(void *arg)
{
	t_phil	*philo;

	philo = (t_phil *)arg;
	ft_eat(*philo);
	//check_death(*philo);
	ft_sleep(*philo); //apres manger
	ft_think(*philo); //think en attendant de pouvoir manger
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
	if(philo.nb_philo == philo.access_table->nb_of_philo - 1)
		pthread_mutex_lock(philo.access_table->p[0].fork);
	else
		pthread_mutex_lock(philo.access_table->p[philo.nb_philo + 1].fork);
	pthread_mutex_lock(&philo.access_table->print);
	printf("%lld %d has taken a fork\n", (init_ms() - philo.access_table->time_of_day), philo.nb_philo);
	printf("%lld %d is eating\n", (init_ms() - philo.access_table->time_of_day), philo.nb_philo);
	pthread_mutex_unlock(&philo.access_table->print);
	philo.nb_time_to_eat += 1;
	ft_usleep(philo.access_table->time_to_eat);
	printf("nbtimetoeat1 = %d\n", philo.time_before_dying);
	philo.time_before_dying = (philo.time_before_dying + philo.access_table->time_to_eat);
	printf("nbtimetoeat2 = %d\n", philo.time_before_dying);
	pthread_mutex_unlock(philo.fork);
	if(philo.nb_philo == philo.access_table->nb_of_philo - 1)
		pthread_mutex_unlock(philo.access_table->p[0].fork);
	else
		pthread_mutex_unlock(philo.access_table->p[philo.nb_philo + 1].fork);
}

void	ft_sleep(t_phil philo)
{
	pthread_mutex_lock(&philo.access_table->print);
	printf("%lld %d is sleeping\n", (init_ms() - philo.access_table->time_of_day), philo.nb_philo);
	pthread_mutex_unlock(&philo.access_table->print);
	ft_usleep(philo.access_table->time_to_sleep);
}

void	ft_think(t_phil philo)
{
	pthread_mutex_lock(&philo.access_table->print);
	printf("%lld %d is thinking\n", (init_ms() - philo.access_table->time_of_day), philo.nb_philo);
	pthread_mutex_unlock(&philo.access_table->print);
}

//si le philo n'a fait qu'attendre car impossibilite de manger
int		check_death(t_phil philo)
{
	printf("w = %lld\n", (init_ms() - philo.access_table->time_of_day));
	if(philo.time_before_dying)
	{
		pthread_mutex_lock(&philo.access_table->print);
		printf("%lld %d died\n", (init_ms() - philo.access_table->time_of_day), philo.nb_philo);
		return(1);
	}
	return(0);
}


//./philo 4 800 200 200
//4 nb_philo 800 timetodie 200 timetoeat 200 timetosleep
int	main(int argc, char **argv)
{
	t_t table;

	if(check_arg(argc, argv) == 1)
		return(1);
	init_struct(&table, argv);
	//free(table.p.philo);
	return (0);
}
