/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:33:26 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/07 20:20:51 by rdcm             ###   ########.fr       */
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
	ft_printf("Server's PID: %d\n", getpid());
	my_signal(SIGUSR1, signal_handler, 0);
	my_signal(SIGUSR2, signal_handler, 0);
	while (1)
		pause();
}
