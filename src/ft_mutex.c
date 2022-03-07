/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe < rrajaobe@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:00:17 by rrajaobe          #+#    #+#             */
/*   Updated: 2022/03/07 09:13:13 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h" 

void	ft_mutex_init(t_args *args, t_thread *thread)
{
	int i;

	i = 0;
	args->forks = malloc(sizeof(pthread_mutex_t) * args->philosophers);
	if (args->forks == 0)
			return ;
	while (i < args->philosophers)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&thread->printer, NULL);
	pthread_mutex_init(&thread->threads, NULL);
	pthread_mutex_init(&thread->mutex, NULL);
	pthread_mutex_init(&thread->lock, NULL);
}

void	ft_mutex_destroy(t_args *args, t_thread *thread)
{
	int i;
	
	i = 0;
	while (i < args->philosophers)
	{
		pthread_join(thread[i].t, NULL);
		i++;
	}
	while (i--)
		pthread_mutex_destroy(&thread->args_obj->forks[i]);
	pthread_mutex_destroy(&thread->mutex);
	pthread_mutex_destroy(&thread->printer);
	pthread_mutex_destroy(&thread->threads);
	pthread_mutex_destroy(&thread->lock);
	ft_free(thread, args);
}

void	ft_mutex_unlock(t_thread *thread)
{
	pthread_mutex_unlock(thread->fork1);
	pthread_mutex_unlock(thread->fork2);
	pthread_mutex_unlock(&thread->lock);
	pthread_mutex_unlock(&thread->printer);
	pthread_mutex_unlock(&thread->mutex);
	pthread_mutex_unlock(&thread->threads);
	pthread_mutex_unlock(thread->args_obj->forks);
}

void	ft_mutex_lock(t_thread *thread)
{
	pthread_mutex_lock(thread->args_obj->forks);
	pthread_mutex_lock(&thread->printer);
	pthread_mutex_lock(&thread->threads);
}