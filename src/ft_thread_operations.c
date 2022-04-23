/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe <rrajaobe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 10:09:22 by rrajaobe          #+#    #+#             */
/*   Updated: 2022/04/23 09:25:23 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	sleeping(long eat_time)
{
	long	sleep_time_starter;

	sleep_time_starter = current_time();
	while (eat_time + sleep_time_starter > current_time())
		usleep(100);
	return ;
}

void	printer(t_thread *thread, char op)
{
	long	time;

	pthread_mutex_lock(&thread->printer);
	if (thread->args_obj->end == FALSE)
	{
		time = current_time() - thread->args_obj->time_start;
		if (op == 'e')
			printf("%ld	%d	is eating\n", time, thread->id);
		else if (op == 's')
			printf("%ld	%d	is sleeping\n", time, thread->id);
		else if (op == 't')
			printf("%ld	%d	is thinking\n", time, thread->id);
		else if (op == 'l' || op == 'r')
			printf("%ld	%d	has taken a fork\n", time, thread->id);
		else if (op == 'd')
		{
			pthread_mutex_lock(&thread->lock);
			thread->args_obj->end = TRUE;
			pthread_mutex_unlock(&thread->lock);
			printf("%ld	%d	died\n", time, thread->id);
			return ;
		}
	}
	pthread_mutex_unlock(&thread->printer);
}

void	eat(t_thread *thread)
{
	if (thread->args_obj->end == FALSE)
	{
		pthread_mutex_lock(thread->fork1);
		printer(thread, 'l');
		pthread_mutex_lock(thread->fork2);
		printer(thread, 'r');
		printer(thread, 'e');
		sleeping(thread->args_obj->eat);
		thread->death = current_time() + thread->args_obj->die;
		thread->philo_eat_counter -= 1;
		pthread_mutex_unlock(thread->fork1);
		pthread_mutex_unlock(thread->fork2);
		if (thread->philo_eat_counter == 0)
		{
			thread->exit = TRUE;
			ft_mutex_unlock(thread);
		}
	}
}

int	current_time(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000);
	ms += (tv.tv_usec / 1000);
	return (ms);
}
