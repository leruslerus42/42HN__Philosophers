/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe < rrajaobe@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 05:38:57 by rrajaobe          #+#    #+#             */
/*   Updated: 2022/03/07 09:42:08 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h> 
# include <limits.h>

# define TRUE 1
# define FALSE 0
# define ERROR "Error \n";

//initalize by using the function:      gcc -g -pthread main.c -o main

//COMPILE:                          gcc -pthread -o a.out main.c

typedef struct s_args
{
	int             philosophers;
	int             die;
	int             eat;
	int             sleep;
	int             full_belly;
	pthread_mutex_t *forks;
long            time_start;
	int				end;
	int				temp;
}   t_args;

typedef struct s_thread
{
	t_args          *args_obj;
	pthread_mutex_t *fork1;
	pthread_mutex_t *fork2;
	pthread_mutex_t lock;
	pthread_mutex_t	printer;
	pthread_mutex_t	mutex;
	pthread_mutex_t	threads;
	pthread_t		t;
	int				id;
	long			death;
	int				philo_eat_counter;
	int				exit;
}   t_thread;

//int main (int argc, char **argv);

/****************PARSING**************/
t_args	*parsing(int argc, char **argv);

/****************MUTEX**************/
void	ft_mutex_init(t_args *args, t_thread *thread);
void	ft_mutex_destroy(t_args *args, t_thread *thread);
void	ft_mutex_unlock(t_thread *thread);
void	ft_mutex_lock(t_thread *thread);

/****************THREAD**************/
void    ft_create_thread(t_args *args, t_thread *thread);
void	*ft_philosophers(void *param);
void	*guardian_thread(void *param);
void	philo(t_thread *thread,t_args *args);

/***********THREAD_OPERATIONS********/
void	eat(t_thread *thread);
void	sleeping(long time);
int		current_time (void);
void	printer(t_thread *thread, char op);

/****************UTILS**************/
void    end_of_program(t_thread *thread);
void    ft_free(t_thread *thread, t_args *args);




# endif
