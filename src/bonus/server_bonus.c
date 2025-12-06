/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:34:44 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/06 12:14:30 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int g_client_pid = 0;

void	signal_handler(int signum)
{
	static int		counter = 0;
	static char		binary[8];
	char			c;

	if (g_client_pid != 0)
		kill(g_client_pid, SIGUSR1);
	usleep(10);
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

void	pid_handler(int signum, siginfo_t *info, void *context)
{
	struct sigaction	sa_bits;

	(void)signum;
	(void)context;

	g_client_pid = info->si_pid;
	ft_printf("\nPID: %d\n", g_client_pid);
	sa_bits.sa_handler = signal_handler;
    sigemptyset(&sa_bits.sa_mask);
    sa_bits.sa_flags = 0;
    sigaction(SIGUSR2, &sa_bits, NULL);
	kill(g_client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	signal_received;
	struct sigaction	signal_pid;


	ft_printf("Server's PID: %d\n", getpid());
	signal_received.sa_handler = signal_handler;
	sigemptyset(&signal_received.sa_mask);
	sigaddset(&signal_received.sa_mask, SIGUSR1);
	sigaddset(&signal_received.sa_mask, SIGUSR2);
	signal_received.sa_flags = 0;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);

	signal_pid.sa_sigaction = pid_handler;
	sigemptyset(&signal_pid.sa_mask);
	signal_pid.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &signal_pid, NULL);
	while (1)
		pause();
}
