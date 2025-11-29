/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:34:44 by rida-cos          #+#    #+#             */
/*   Updated: 2025/11/29 17:50:26 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum)
{
	static int	counter = 0;
	char		binary[8];

	if (signum == SIGUSR1)
	{
		binary[counter] = 0;
	}
	else if (signum == SIGUSR2)
	{
		binary[counter] = 1;
	}
	counter++;
	if (counter == 8)
	{
		// ft_printf("%d%d%d%d%d%d%d%d\n", binary[0], binary[1], binary[2], binary[3], binary[4], binary[5], binary[6], binary[7]);
		// ft_printf("Caractere: %c ASCII: %d\n", convert_to_integer(binary), convert_to_integer(binary));
		ft_printf("%c", convert_to_integer(binary));
		counter = 0;
	}
}

int	main(void)
{
	struct sigaction	signal_received;

	ft_printf("Server's PID: %d\n", getpid());
	signal_received.sa_handler = signal_handler;
	signal_received.sa_flags = 0;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
		usleep(50);
}
