/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:23:16 by clecat            #+#    #+#             */
/*   Updated: 2022/10/04 16:19:49 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

/*fonction autorisee : memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/

//a regler seg fault au dernier philo au premier make

/*{table: tous les times les philos }
{philo: fork num time to eat}*/
//voir thread et mutex

/* nb philo = nb fourchette
time_to_die = le temps qu'il a avant de mourir
time_to_eat = le temps qu'il a pour manger et qu'il bloque les 2 fourchettes 
time_to_sleep = temps qu'il passe a dormir
nb_of_times_each_philo_must_eat = le nb de fois qu'un philo doit manger
les philo ne doivent pas mourir 
chaque philo representer par un thread*/

/* preferer faire 5 usleep(10)
qu'un usleep(50) car pas tres precies
argv[1] = number_of_philosophers
argv[2] = time_to_die
argv[3] = time_to_eat
argv[4] = time_to_sleep
optionnelle argv[5] = number_of_times_each_philosopher_must_eat
3 actions autoriser manger, penser, dormir
proteger les fork avec des mutex; philosophe numéro N est assis entre philosophe
numéro N - 1 et philosophe numéro N + 1.*/


/*lancer les threads  dans une autre boucle et faire la routine (eat sleep think) 
rajouter un mutex pour l ecriture usleep()*/

// routinephilo : manger, penser et dormir 
//(mourir si le temps est depasser )
void	*routine(t_t table)
{
	(void) table;
	//pthread_mutex_lock(&table.p.fork);
	write(1, "je suis un thread\n", 19);
	//pthread_mutex_unlock(&table.p.fork);
	return NULL;
}

int	main(int argc, char **argv)
{
	t_t table;
	printf("argc = %d\n", argc);
	check_arg(argc, argv);
	init_struct(&table, argv);
	int i = 0;
	while (i < table.nb_of_philo)
	{
		table.p[i].fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(table.p[i].fork, NULL);
		pthread_create(&table.p[i].philo, NULL, routine(table), NULL);
		printf("Philo %d has started\n", i);
		i++;
	}
	fork_init(table);
	printf("test1\n");
	/*int ret;
	while (i == table.nb_of_philo)
	{
		void *retval;
		printf("test\n");
		ret = pthread_join(table.p->philo, &retval);
		if (retval == PTHREAD_CANCELED)
            printf("The thread was canceled - ");
        else
            printf("Returned value %d - ", (int)retval);

		if(pthread_join(table.p->philo, NULL) != 0)
			return 2;
		printf("test\n");
		printf("Philo %d has finished exec\n", i);
		i--;
	}*/
	//free(table.p.philo);
	//check_arg(argc);
	return (0);
}

/* timestamp_in_ms X has taken a fork / is eating / is sleeping / is thinking / died
mange pense dort ; nb paire et impaire de philo 
3 philo = 1 finira par mourir */