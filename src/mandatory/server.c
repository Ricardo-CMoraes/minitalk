/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:34:44 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/02 22:55:50 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum)
{
	static int	counter = 0;
	char		binary[8];

	if (signum == SIGUSR1)
		binary[counter] = 0;
	else if (signum == SIGUSR2)
		binary[counter] = 1;
	counter++;
	if (counter == 8)
	{
		ft_printf("%c", convert_to_integer(binary));
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
