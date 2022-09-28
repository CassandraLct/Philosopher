/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:30:08 by clecat            #+#    #+#             */
/*   Updated: 2022/06/17 12:42:54 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

//check que des digit et que 5 ou 6 arg
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
				return(printf("Error : arg not digit\n"));
			j++;
		}
		j = 0;
		i++;
	}
	return(0);
}

void	check_arg(int argc)
{
	if (argc < 5)
		write(1, "Missing arguments\n", 18);
	else if (argc > 6)
		write(1, "Too much arguments\n", 19);
}