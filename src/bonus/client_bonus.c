/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:53:52 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/02 00:03:59 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t g_ack_received = 0;

char	*convert_to_binary(int number)
{
	int		i;
	char	*b;

	b = malloc(sizeof(char) * 8);
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

void	ack_handler(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

void	send_message(int pid, char *message)
{
	char	*binary;
	int		i;
	int		j;

	j = 0;
	while (message[j])
	{
		binary = convert_to_binary(message[j]);
		i = 0;
		while (i < 8)
		{
			if (binary[i] == 0)
			{
				kill(pid, SIGUSR1);
			}
			else
			{
				kill(pid, SIGUSR2);
			}
			i++;
		}
		ft_printf("%c", convert_to_integer(binary));
		free(binary);
		j++;
		g_ack_received = 0;
		while (g_ack_received == 0)
			pause();
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		g_ack_received = 0;
		while (g_ack_received == 0)
			pause(); 
	}
	ft_printf("%d", pid);
}

void	send_pid(int server_pid)
{
    if (kill(server_pid, SIGUSR2) == -1)
    {
        ft_putstr_fd("Erro: Não foi possível enviar o sinal inicial para o PID do servidor.\n", 2);
        exit(EXIT_FAILURE);
    }
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;
	struct sigaction	signal_ack;

	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	if (!pid)
		return (1);
	message = argv[2];
	signal_ack.sa_handler = ack_handler;
	sigemptyset(&signal_ack.sa_mask);
	signal_ack.sa_flags = 0;
	if (sigaction(SIGUSR1, &signal_ack, NULL) == -1)
	{
		ft_putstr_fd("Erro ao configurar o handler de ACK.\n", 2);
		return (1);
	}
	send_pid(pid);
	send_message(pid, message);
	ft_printf("\n");
}
