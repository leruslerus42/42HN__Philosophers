/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe < rrajaobe@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:37:39 by rrajaobe          #+#    #+#             */
/*   Updated: 2022/04/11 12:45:38 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *guardian_thread(void *param)
{
	t_thread	*guardian_thread;
	int			i;

	i = 0;
	guardian_thread = (t_thread *)param;
	while (TRUE)
	{
		if (current_time() >= guardian_thread[i].death)
		{
			printer(&guardian_thread[i], 'd');
			end_of_program(guardian_thread);
			if (guardian_thread[i].args_obj->end == TRUE)
				return (NULL);
		}
		i++;
		if (i >= guardian_thread[0].args_obj->philosophers)
			i = 0;
	}
	return (NULL);
}

void *ft_philosophers(void *param)
{
	t_thread	*thread;

	thread = (t_thread *)param;
	pthread_mutex_lock(&thread->threads);
	while (thread->exit == TRUE)
	{
		if (thread->args_obj->end == FALSE)
		{
			thread->death = current_time() + thread->args_obj->die;
			eat(thread);
			if (thread->exit == TRUE)
			{
				printer(thread, 's');
				sleeping(thread->args_obj->sleep);
				printer(thread, 't');
			}
		}
	}
	pthread_mutex_unlock(&thread->threads);
	ft_mutex_unlock(thread);
	return (NULL);
}

void    ft_create_thread(t_args *args, t_thread *thread)
{
	pthread_t	_guardian_thread;

	args->temp = 0;
	args->time_start = current_time();
	while (args->temp < args->philosophers)
	{
		if (args->temp % 2 == 0)
			pthread_create(&thread[args->temp].t, NULL, &ft_philosophers, &thread[args->temp]);
		usleep(100);
		args->temp ++;
	}
	usleep(100);
	args->temp = 0;
	while (args->temp < args->philosophers)
	{
		if (args->temp % 2 != 0)
			pthread_create(&thread[args->temp].t, NULL, &ft_philosophers, &thread[args->temp]);
		usleep(100);
		args->temp ++;
	}
	pthread_create(&_guardian_thread, NULL, &guardian_thread, thread);
	
}

void	philo(t_thread *thread,t_args *args)
{
	while (args->temp < args->philosophers)
	{
		thread[args->temp].args_obj = args;
		thread[args->temp].id = args->temp + 1;
		thread[args->temp].philo_eat_counter = args->full_belly;
		if (args->temp < args->philosophers)
		{
			thread[args->temp].fork1 = &args->forks[args->temp];
			thread[args->temp].exit = TRUE;
			if (args->temp == 0)
				thread[args->temp].fork2 = &args->forks[args->philosophers -1];
			else
				thread[args->temp].fork2 = &args->forks[args->temp -1];
		}
		args->temp ++;
		/*thread[i].args = args;
		thread[i].philo_eat_counter = args->full_belly;
		thread[i].id = ++i;*/
	}

		ft_create_thread(args, thread);
}
	
/*
void	philo(t_thread *thread,t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philosophers)
	{
		if (i < args->philosophers)
		{
			thread[i].fork1 = &args->forks[i];
			thread[i].exit = FALSE;
			if (!i)
				thread[i].fork2 = &args->forks[i-1];
			else
				thread[i].fork2 = &args->forks[args->philosophers];
		}
		thread[i].args = args;
		thread[i].philo_eat_counter = args->full_belly;
		thread[i].id = ++i;
	}
}*/
