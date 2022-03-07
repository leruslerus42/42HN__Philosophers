/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe < rrajaobe@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 10:09:22 by rrajaobe          #+#    #+#             */
/*   Updated: 2022/03/07 10:30:17 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	sleeping(long time)
{
	long	time_begin;

	time_begin = current_time();
	while (time + time_begin > current_time())
		usleep(100);
	return ;

}

void printer(t_thread *thread, char op)
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
			printf("%ld %d	is thinking\n", time, thread->id);
		else if (op == 'f')
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

void    eat(t_thread *thread)
{
	if (thread->args_obj->end == FALSE)
	{
		pthread_mutex_lock(thread->fork1);//CHANGE: mehrere threads konnten gleich fork nehmen ->DEADLOCK
		printer(thread, 'f');//
		pthread_mutex_lock(thread->fork2);//
		printer(thread, 'f');
		printer(thread,'e');
		sleeping(thread->args_obj->eat);
		thread->death = current_time() + thread->args_obj->die;
		thread->philo_eat_counter -= 1;
		pthread_mutex_unlock(thread->fork1);
		pthread_mutex_unlock(thread->fork2);
		if (thread->philo_eat_counter == 0)
		{
			thread->exit = 0;
			ft_mutex_unlock(thread);
		}

	}
}



int current_time (void)
{
	struct timeval tv;
	long			ms;
	
	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000);
	ms += (tv.tv_usec / 1000);
	return (ms);
}
