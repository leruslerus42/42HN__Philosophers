/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe < rrajaobe@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:42:16 by rrajaobe          #+#    #+#             */
/*   Updated: 2022/04/18 05:52:25 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"


/*
ARGS
[1] number of philos && forks
[2] time to die: if a PHILO doesn't start to eat after their last meal or beginn -> DEAD (ms)
[3] time to eat: time it takes to eat, keeping two forks (ms)
[4] time to sleep: time of sleep (ms)
[5] number of tries each PHILO must eat, fakultativ: if specifeid, when all PHILOS eat at least this number, the simulation stops.

RULES
- Each Philo has a number between 1 and [1]
- Maximal time between a PHILO's death and the printing message: 10 ms
PRINTING
- [] X has taken a fork
- [] X is eating / sleeping / thinking / died
[] replaced by the timestamp in ms, X by th PHILO's number

*/

int main (int argc, char **argv)
{
	t_args		*args;
	t_thread	*thread;

	args = parsing(argc, argv);
	if (!args)
		return (-1);
	thread = malloc(sizeof(t_thread) * (args->philosophers + 1));
	if (!thread)
		return (-1);
	ft_mutex_init(args, thread);
	philo(thread, args);
	ft_mutex_destroy(args, thread);//mutex should be unlocked, otherwise undefined behaviour
	return (0);
}
