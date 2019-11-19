/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:58:29 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 19:07:57 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include <stdio.h>

void		init_jobs_struct(void)
{
	t_jobs	*jobs;

	if (!(jobs = malloc(sizeof(t_jobs))))
		return ;
	jobs->is_jobs = 0;
	jobs->index = 1;
	jobs->lst = NULL;
	g_shell.jobs = jobs;
}

void		jobs_insert(t_jobs_lst *job)
{
	t_jobs_lst	*curr;

	curr = g_shell.jobs->lst;
	if (!curr)
		g_shell.jobs->lst = job;
	else
	{
		while (curr->next)
			curr = curr->next;
		job->prev = curr;
		job->next = NULL;
		curr->next = job;
	}
}

t_jobs_lst	*new_job(t_anode *ast)
{
	t_jobs_lst *new_elem;

	if (!g_shell.jobs)
		init_jobs_struct();
	if (!(new_elem = malloc(sizeof(t_jobs_lst))))
		return (NULL);
	new_elem->ast = ast;
	new_elem->job_number = g_shell.jobs->index++;
	new_elem->pid = 0;
	new_elem->status = 0;
	new_elem->prev = NULL;
	new_elem->next = NULL;
	jobs_insert(new_elem);
	return (new_elem);
}
