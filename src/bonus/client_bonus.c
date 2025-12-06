/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:53:52 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/06 12:06:18 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static volatile sig_atomic_t g_ack_received = 0;

void	ack_handler(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

char	*convert_to_binary(int number)
{
	int		i;
	char	*b;

	b = malloc(sizeof(char) * 8);
	if (!b)
		handle_error("Error: memory allocation\n");
	ft_memset(b, 0, sizeof(b));
	i = 7;
	while (number > 0)
	{
		b[i] = (number % 2);
		number = number / 2;
		i--;
	}
	return (b);
}

void	send_message(int pid, char *message)
{
	char	*binary;
	int		i;
	int		j;

	j = 0;
	while (message[j])
	{
		ft_printf("\n");
		binary = convert_to_binary(message[j]);
		i = 0;
		while (i < 8)
		{
			if (binary[i] == 0)
			{
				ft_printf("0");
				send_bit_and_wait(pid, SIGUSR1);
			}
			else
			{
				ft_printf("1");
				send_bit_and_wait(pid, SIGUSR2);
			}
			i++;
		}
		free(binary);
		j++;
	}
	i = 0;
	while (i++ < 8)
	{
		send_bit_and_wait(pid, SIGUSR1);
		ft_printf("0");
	}
}

void	send_pid(int server_pid)
{
	if (kill(server_pid, SIGUSR2) == -1)
		handle_error("Error: Failure to send pid");
	g_ack_received = 0;
	while (g_ack_received == 0)
		pause();
}

void	send_bit_and_wait(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		handle_error("Error: process does not exist or invalid pid\n");
	g_ack_received = 0;
	while (g_ack_received == 0)
		pause();
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*message;
	struct sigaction	signal_ack;

	if (argc != 3)
		handle_error("Error: more or less than three arguments\n");
	pid = ft_atoi(argv[1]);
	if (!(pid > 0))
		handle_error("Error: wrong pid\n");
	message = argv[2];
	signal_ack.sa_handler = ack_handler;
	sigemptyset(&signal_ack.sa_mask);
	signal_ack.sa_flags = 0;
	if (sigaction(SIGUSR1, &signal_ack, NULL) == -1)
		handle_error("Error:ACK configuration.\n");
	if (sigaction(SIGUSR2, &signal_ack, NULL) == -1)
		handle_error("Error:ACK configuration.\n");
	send_pid(pid);
	ft_printf("\nPID: %d\n", getpid());
	send_message(pid, message);
	return (0);
}
