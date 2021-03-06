/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_destroy_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:49:02 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/23 15:45:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"
#include "jobcontrol.h"

static void	kill_jobs(t_shell *shell)
{
	t_jobs_lst	*jobs;

	jobs = shell->jobs.lst;
	while (jobs)
	{
		if (!jobs->pipeline)
		{
			if (jobs->state == JOB_SUSPENDED)
				kill(-jobs->pid, SIGCONT);
			kill(-jobs->pid, SIGHUP);
		}
		else
		{
			if (jobs->state == JOB_SUSPENDED)
				exec_signal_pipe(jobs->pipeline, SIGCONT);
			exec_signal_pipe(jobs->pipeline, SIGHUP);
		}
		jobs = jobs->next;
	}
}

void		jobs_destroy_all(t_shell *shell, int kill)
{
	t_jobs_lst *curr;
	t_jobs_lst *next;

	isatty(0) && kill ? kill_jobs(shell) : 0;
	curr = shell->jobs.lst;
	while (curr)
	{
		next = curr->next;
		exec_del_pipeline(curr->pipeline);
		free(curr->command);
		free(curr);
		curr = next;
	}
	shell->jobs.lst = NULL;
	shell->jobs.minus = NULL;
	shell->jobs.plus = NULL;
	shell->jobs.last_job = NULL;
	shell->jobs.index = 1;
	shell->jobs.len = 1;
}
