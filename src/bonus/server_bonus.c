/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:33:26 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/07 19:59:42 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_state	g_state = {0};

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	char	c;

	(void)context;
	if (info->si_pid != 0)
		g_state.pid = info->si_pid;
	if (g_state.pid != 0)
		kill(g_state.pid, SIGUSR1);
	g_state.accumulator <<= 1;
	if (signum == SIGUSR2)
		g_state.accumulator |= 1;
	g_state.count++;
	if (g_state.count == 8)
	{
		g_state.count = 0;
		if (g_state.accumulator == 0)
		{
			write(1, "\n", 1);
			kill(g_state.pid, SIGUSR2);
			g_state.accumulator = 0;
			return ;
		}
		c = (char)g_state.accumulator;
		write(1, &c, 1);
		g_state.accumulator = 0;
	}
}

int	main(void)
{
	ft_printf("Server's PID: %d\n", getpid());
	my_signal(SIGUSR1, signal_handler, 1);
	my_signal(SIGUSR2, signal_handler, 1);
	while (1)
		pause();
	return (0);
}
