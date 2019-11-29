/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:48:31 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/29 11:44:00 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

static void			jobs_insert(t_jobs_lst *job)
{
	t_jobs_lst	*curr;

	curr = g_shell.jobs.lst;
	if (!curr)
		g_shell.jobs.lst = job;
	else
	{
		while (curr->next)
			curr = curr->next;
		job->prev = curr;
		job->next = NULL;
		curr->next = job;
	}
	if (g_shell.jobs.index > 3)
		g_shell.jobs.last_job->prev->current = ' ';
	if (g_shell.jobs.index > 2)
	{
		g_shell.jobs.minus = g_shell.jobs.last_job;
		g_shell.jobs.last_job->current = '-';
	}
	if (g_shell.jobs.index == 2)
		g_shell.jobs.minus = job;
	g_shell.jobs.last_job = job;
	g_shell.jobs.plus = job;
}

static t_jobs_lst	*new(void)
{
	t_jobs_lst *job;

	if (!(job = (t_jobs_lst *)malloc(sizeof(t_jobs_lst))))
		return (NULL);
	job->command = NULL;
	job->job_number = g_shell.jobs.index++;
	job->pid = 0;
	job->childs = NULL;
	job->current = '+';
	job->state = "Running";
	job->prev = NULL;
	job->next = NULL;
	jobs_insert(job);
	return (job);
}

t_jobs_lst			*job_new(t_cmd *cmd, int pid)
{
	t_jobs_lst *job;

	if (!(job = new()))
		return (NULL);
	job->command = job_get_command(cmd);
	job->pid = pid;
	ft_printf("[%d] %d\n", job->job_number, pid);
	return (job);
}

t_jobs_lst			*job_new_pipe(t_pipel *pline, t_childs *childs)
{
	t_jobs_lst *job;

	if (!(job = new()))
		return (NULL);
	job->command = job_get_pipe_command(pline);
	job->childs = childs;
	if (!childs)
		return (job);
	while (childs->next)
		childs = childs->next;
	ft_printf("[%d] %d\n", job->job_number, childs->pid);
	return (job);
}