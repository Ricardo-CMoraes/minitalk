/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:33:26 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/06 19:00:31 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_state	g_state = {0};

void	signal_handler(int signum)
{
	char	c;

	g_state.accumulator <<= 1;
	if (signum == SIGUSR2)
		g_state.accumulator |= 1;
	g_state.count++;

	if (g_state.count == 8)
	{
		if (g_state.accumulator == 0)
			write(1, "\n", 1);
		else
		{
			c = (char)g_state.accumulator;
			write(1, &c, 1);
		}
		g_state.accumulator = 0;
		g_state.count = 0;
	}
}

int	main(void)
{
	struct sigaction	signal_received;

	ft_printf("Server's PID: %d\n", getpid());
	signal_received.sa_handler = signal_handler;
	sigemptyset(&signal_received.sa_mask);
	sigaddset(&signal_received.sa_mask, SIGUSR1);
	sigaddset(&signal_received.sa_mask, SIGUSR2);
	signal_received.sa_flags = 0;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
		pause();
}
