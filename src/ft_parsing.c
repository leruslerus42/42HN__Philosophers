/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe < rrajaobe@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 07:09:18 by rrajaobe          #+#    #+#             */
/*   Updated: 2022/03/07 08:46:01 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "limits.h"

static int ft_atoi_long(const char *input)
{
	int 			sign;
	long long int	num;

	sign = 1;
	num = 0;
	while ((*input >= 9 && *input <= 13) || *input == ' ')
		input++;
	if (*input == '-' || *input == '+')
	{	
		if (*input == '-')	//check if I can go already here out
			sign *= -1;
		if (*input == '\0')
			return (FALSE);
	}
	while (*input >= '0' && *input <= '9')
		num = num * 10 + *input++ - '0';	
	if (sign * num > INT_MAX || sign * num < 0 || *input != '\0')
		return (FALSE);
	return (num);

}

static t_args *ft_initialize_arguments(t_args *args, int argc, char **argv)
{
	memset(args, 0, sizeof(t_args));
	args->philosophers = ft_atoi_long(argv[1]);
	args->die = ft_atoi_long(argv[2]);
	args->eat = ft_atoi_long(argv[3]);
	args->sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
		args->full_belly = ft_atoi_long(argv[5]);
	else
		args->full_belly = INT_MAX;
	return (args);
}

t_args *parsing(int argc, char **argv)
{
	t_args	*args;
	int		i;

	i = 1;

	if (argc < 5 || argc > 6)
		return (NULL);
	while (i < argc)
	{
		if (!(ft_atoi_long(argv[i])))
			return (NULL);
		i++;
	}
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	ft_initialize_arguments(args, argc, argv);
	return (args);
}
