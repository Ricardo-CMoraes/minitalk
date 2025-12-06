/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:34:44 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/05 21:31:14 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum)
{
	static int		counter = 0;
	static char		binary[8];
	char			c;

	if (signum == SIGUSR1)
		binary[counter] = 0;
	else if (signum == SIGUSR2)
		binary[counter] = 1;
	counter++;
	if (counter == 8)
	{
		if (convert_to_integer(binary) > 127)
			write(1, "!", 1);
		else
		{
			c = (char)convert_to_integer(binary);
			write(1, &c, 1);
		}
		ft_memset(binary, 0, sizeof(binary));
		counter = 0;
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
