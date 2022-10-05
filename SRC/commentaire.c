/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commentaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:12:04 by clecat            #+#    #+#             */
/*   Updated: 2022/10/05 13:30:30 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*pthread_join :
pthread_join attendre la fin d'un autre thread
pthread_join() suspend l'exécution du thread appelant
jusqu'à ce que le thread identifié par th achève son exécution*/

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

/* timestamp_in_ms X has taken a fork / is eating / is sleeping / is thinking / died
mange pense dort ; nb paire et impaire de philo 
3 philo = 1 finira par mourir */

/* pthread_detach :
place un thread dans l'etat detacher, empeche les autres thread
de se synchro sur la mort du thread appeler dans detach*/

/*affichage lorsque chqngement detat de philo
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died*/

/*gettimeofday
utilise la structure :
struct timeval {
    time_t      tv_sec;
    suseconds_t tv_usec;
};
sert a lire l'heure, donc avoir l'heure de debut*/

/*int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}*/
