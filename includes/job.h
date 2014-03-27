/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 14:05:14 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/27 19:15:23 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H

# include <sys/types.h>
# include "struct.h"

void	ft_viewlist_process(t_process *list);
void	ft_add_process(t_process **list, pid_t pid, char **argv);

void	ft_viewlist_job(t_job *lstjob);
void	ft_add_job(t_job **lst_j, pid_t *pid, t_process *process);

void	ft_determine_recent(t_job **list);
int		ft_min_num_job(t_job *lst);
int		ft_max_num_job(t_job *lst);
int		ft_job_completed(t_job *job);

void	ft_destroy_tab(char **tab);
void	ft_destroy_process(t_process **list);
void	ft_destroy_job(t_job **list);

void	ft_check_process_tostop(t_process **lstprocess);
void	ft_stop_job(t_job **lstjob, pid_t pgid);
void	ft_check_process_tocont(t_process **lstprocess);
void	ft_cont_job(t_job **lstjob, pid_t pgid);

/*
** SIGNALS
*/
void	ft_sig_handler(int c);

#endif

