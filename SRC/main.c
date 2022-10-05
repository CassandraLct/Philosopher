/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:23:16 by clecat            #+#    #+#             */
/*   Updated: 2022/10/05 15:51:12 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

/*fonction autorisee : memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/

/*lancer les threads  dans une autre boucle et faire la routine (eat sleep think) 
rajouter un mutex pour l ecriture; usleep()*/

// routinephilo : manger, penser et dormir 
// philo pense en attendant de pouvoir manger
// (mourir si le temps est depasser)
void	*routine(void *arg)
{
	t_phil *philo;
	
	philo = (t_phil *)arg;
	ft_eat(*philo);
	return NULL;
}

/*timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died*/
//acces fork_left fait automatiquement avec unlock
//affichage temp en ms avec init_ms
void	ft_eat(t_phil philo)
{
	printf("1\n");
	pthread_mutex_lock(philo.fork);
	printf("2\n");
	pthread_mutex_lock(philo.access_table->p[nb_philo + 1]);
	printf("3\n");
	pthread_mutex_lock(&philo.access_table->print);
	printf("4\n");
	printf("%lld %d has taken a fork\n", (init_ms() - philo.access_table->time_of_day), philo.nb_philo);
	pthread_mutex_unlock(&philo.access_table->print);
	pthread_mutex_lock(&philo.access_table->print);
	printf("%lld %d is eating\n", (init_ms() - philo.access_table->time_of_day), philo.nb_philo);
	pthread_mutex_unlock(&philo.access_table->print);
	ft_usleep(philo.access_table->time_to_eat);
	printf("pass \n");
	/*if(check_death(philo) == 1)
	{
		printf("%lld %d died\n", (init_ms() - philo.access_table->time_of_day), philo.nb_philo);
	}*/
	pthread_mutex_unlock(philo.fork);
	pthread_mutex_unlock(philo.fork_left);
	//display("(temp en ms)(p)1 has taken a fork\n");
}

/*int		check_death(t_phil philo)
{
	if()
		return(1);
	return(0);
}*/

int	main(int argc, char **argv)
{
	t_t table;

	if(check_arg(argc, argv) == 1)
		return(1);
	init_struct(&table, argv);
	fork_init(table);
	//free(table.p.philo);
	return (0);
}
