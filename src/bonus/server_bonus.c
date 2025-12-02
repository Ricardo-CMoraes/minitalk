/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:34:44 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/01 23:54:24 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int g_client_pid = 0;

void	signal_handler(int signum)
{
	static int		counter = 0;
	static char		binary[8];
	int				received_char;

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
		received_char = convert_to_integer(binary);
		write(1, &received_char, 1);
		ft_memset(binary, 0, sizeof(binary));
		counter = 0;
		if (g_client_pid != 0)
			kill(g_client_pid, SIGUSR1);
	}
}

void	pid_handler(int signum, siginfo_t *info, void *context)
{
    (void)signum;
    (void)context;
    
    g_client_pid = info->si_pid;
    
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
