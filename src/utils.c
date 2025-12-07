/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:56:37 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/07 20:14:10 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_error(const char *msg)
{
	ft_printf(msg);
	exit(EXIT_FAILURE);
}

void	send_bit(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		handle_error("Error: process does not exist\n");
	usleep(UWAIT);
}

void	my_signal(int signum, void *handler, int use_siginfo)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (use_siginfo == 1)
	{
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
	}
	else
		sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(signum, &sa, NULL) < 0)
		handle_error("Signal handler setup failed");
}

void	my_kill(pid_t pid, int signum)
{
	if (kill(pid, signum) < 0)
		handle_error("Signal transmission failed");
}
