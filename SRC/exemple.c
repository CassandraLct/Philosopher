/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exemple.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:00:44 by clecat            #+#    #+#             */
/*   Updated: 2022/10/05 14:04:22 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//exemple thread

/*int var = 10;
pthread_mutex_t lock;

void	*routine()
{
    int r = rand() % 10;
	write(1, "je suis un thread\n", 19);
	return NULL;
}

int main()
{
	pthread_t *philo;
	
	pthread_mutex_init(&lock, NULL);

	philo = malloc(10 * sizeof(pthread_t));
	int i = -1;
	
	while (++i != 10)
		pthread_create(&philo[i], NULL, routine, NULL);
	sleep(20);
	printf("%d\n", var);
	return(0);
}*/

/*codevault thread*/

int mails = 0;
int lock = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	int i = 0;

	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	i++;
	/*printf("tests from threads\n");
	sleep(3);
	printf("ending threads\n");*/
}

int main(int argc, char **argv)
{
	pthread_t th[4];
	int i;
	
	pthread_mutex_init(&mutex, NULL);
	while (th[i])
	{
		if (pthread_create(th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread\n");
			return 1;	
		}
		printf("Thread %d has started\n");
		if (pthread_join(th[i], NULL) != 0)
			return 2;
	}
	i++;
	pthread_mutex_destroy(&mutex);
	printf("Number of mails = %d\n", mails);
	return(0);
}


/* recupere la valeur de retour de pthread join
int ret;
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
	printf("Philo %d has finished exec\n", i);
	i--;
}*/