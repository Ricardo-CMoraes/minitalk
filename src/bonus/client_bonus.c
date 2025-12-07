/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:58:06 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/07 19:47:47 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t g_ack_received = 0;

void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((i >> bit) & 1)
			my_kill(pid, SIGUSR2);
		else
			my_kill(pid, SIGUSR1);
		bit--;
		while (g_ack_received == 0)
			usleep(42);
		g_ack_received = 0;
	}
}

static void	end_handler(int signum)
{
	(void)signum;
	ft_printf("\n\t✅ Message received ✅\n");
	exit(EXIT_SUCCESS);
}

static void	ack_handler(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

int	main(int argc, char **argv)
{
	pid_t		pid;
	char	*message;
	int		i;
	
	if (argc != 3)
		handle_error("Error: more or less than three arguments\n");
	pid = ft_atoi(argv[1]);
	if (!(pid > 0))
		handle_error("Error: wrong pid\n");
	message = argv[2];

	my_signal(SIGUSR1, ack_handler, 0);
	my_signal(SIGUSR2, end_handler, 0);

	i = 0;
	while (message[i] != '\0')
	{
		ft_send_bits(pid, message[i]);
		i++;
	}
	ft_send_bits(pid, '\0');
	return (0);
}
