/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:43:00 by clecat            #+#    #+#             */
/*   Updated: 2022/10/05 13:30:25 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_digit(char **argv)
{
	int i;
	int j;
	
	i = 1;
	j = 0;
	while(argv[i] != '\0')
	{
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf("argv[%d] is not a digit\n", i);
				return(1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return(0);
}