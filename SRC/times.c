/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:44:28 by clecat            #+#    #+#             */
/*   Updated: 2022/10/05 13:49:41 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

//tv_sec = seconde; tv_usec = microseconde
long    init_ms(void)
{
    struct timeval  timestruct;
    long long       ms;
    gettimeofday(&timestruct, NULL);
    ms = timestruct.tv_sec * 1000 + timestruct.tv_usec / 1000;
    return (ms);
}

// le philo attend pendant x temp
void    ft_usleep(long time)
{
    long    start_time;
    start_time = init_ms();
    while (init_ms() - start_time < time)
        usleep(time * 10);
}

//fonction d'affichage
void	display(char *str)
{
	printf("%s\n", str);
}