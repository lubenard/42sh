/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:48:31 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/14 17:36:17 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"
#include "execution.h"

static void			jobs_insert(t_jobs_lst *job)
{
	t_jobs_lst	*curr;

	g_shell.jobs.len++;
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
	if (g_shell.jobs.len > 2)
		g_shell.jobs.last_job->prev->current = ' ';
	if (g_shell.jobs.len > 1)
	{
		g_shell.jobs.minus = g_shell.jobs.last_job;
		g_shell.jobs.last_job->current = '-';
	}
	if (g_shell.jobs.len == 1)
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
	job->pipeline = NULL;
	job->current = '+';
	job->status = "Running";
	job->state = JOB_RUNNING;
	tcgetattr(g_shell.pgrp, &job->tmodes);
	job->tmodes.c_lflag = g_shell.prev_term.c_lflag;
	job->prev = NULL;
	job->next = NULL;
	job->foreground = 0;
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
	isatty(0) ? ft_printf("[%d] %d\n", job->job_number, pid) : 0;
	return (job);
}

t_jobs_lst			*job_new_pipe(t_pipel *pline)
{
	t_jobs_lst *job;

	if (!(job = new()))
		return (NULL);
	job->command = job_get_pipe_command(pline);
	job->pipeline = exec_dup_pipeline(pline);
	ft_printf("PIPELINE: %p\n", job->pipeline);
	if (!pline)
		return (job);
	while (pline->next)
		pline = pline->next;
	isatty(0) ? ft_printf("[%d] %d\n", job->job_number, pline->pid) : 0;
	return (job);
}
