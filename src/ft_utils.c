/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe < rrajaobe@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 08:56:12 by rrajaobe          #+#    #+#             */
/*   Updated: 2022/04/18 06:05:18 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void    end_of_program(t_thread *thread)
{
	int i;

	i = 0;
	while (i < thread->args_obj->philosophers)
	{
		thread[i].args_obj->end = TRUE;
		thread[i].exit = 0;
		ft_mutex_unlock(&thread[i]);
		i++;
	}
}

void    ft_free(t_thread *thread, t_args *args)
{
	free(args->forks);
	free(args);
	free(thread);
}