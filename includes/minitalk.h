/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:58:13 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/07 20:30:34 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# define UWAIT 250

typedef struct s_state
{
	int		accumulator;
	int		count;
	pid_t	pid;
}	t_state;

void	handle_error(const char *msg);
void	send_bit(int pid, int signal);
void	my_signal(int sig, void *handler, int use_siginfo);
void	my_kill(pid_t pid, int signum);

#endif
