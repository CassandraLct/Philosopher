/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:31:42 by clecat            #+#    #+#             */
/*   Updated: 2022/10/10 14:52:37 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <fcntl.h>

//struct philo
typedef struct	s_phil 
{
	pthread_t philo;
	int nb_fork;
	int nb_time_to_eat;
	int nb_philo;
	int time_before_dying;
	pthread_mutex_t *fork;
	pthread_mutex_t *fork_left;
	struct s_t *access_table;
}	t_phil;

//structure generale
typedef struct s_t
{
    int 		nb_of_philo;
    int 		nb_of_fork;
	int 		time_to_eat;
	int 		time_to_sleep;
	int			time_to_die;
	int			nb_of_times_each_philo_must_eat;
	long long	time_of_day;
	pthread_mutex_t print;
	t_phil	*p;
} 	t_t;

int		check_arg(int argc, char **argv);
int		check_digit(char **argv);
int		ft_atoi(const char *str);
int		init_struct(t_t *table, char **argv);
void	*routine(void *arg);
int		ft_isdigit(int c);
int		init_philo(t_t *table);
long    init_ms(void);
void    ft_usleep(long time);
void	ft_eat(t_phil philo);
void	ft_sleep(t_phil philo);
void	ft_think(t_phil philo);
int		check_death(t_phil philo);

#endif