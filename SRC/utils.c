/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:43:00 by clecat            #+#    #+#             */
/*   Updated: 2022/10/04 14:33:53 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

/*fonction autorisee:
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy,pthread_mutex_lock,
pthread_mutex_unlock*/

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int ft_atoi(const char *str)
{
	int i = 0;
	int sign = 1;
	int res = 0;

	if(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if(str[i] == '+' || str[i] == '-')
	{
		if(str[i] == '-')
			sign *= -1;
		i++;
	}
	if(!(str[i] >= '0' && str[i] <= '9'))
		return(0);
	while(str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return(res * sign);
}