/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:31:42 by clecat            #+#    #+#             */
/*   Updated: 2022/10/04 16:20:06 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

//struct philo
typedef struct	s_phil 
{
	pthread_t philo;
	int nb_fork;
	int time_to_eat;
	int nb_philo;	
	pthread_mutex_t *fork;
	pthread_mutex_t *fork_left;
}	t_phil;

//structure generale
typedef struct s_t
{
    int nb_of_philo;
    int nb_of_fork;
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	t_phil	*p;
} 	t_t;

void	check_arg(int argc, char **argv);
int check_digit(char **argv);
int ft_atoi(const char *str);
void init_struct(t_t *table, char **argv);
void fork_init(t_t table);

#endif