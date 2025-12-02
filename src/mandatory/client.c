/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:53:52 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/02 00:13:05 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
			usleep(50);
			i++;
		}
		ft_printf("%c", convert_to_integer(binary));
		free(binary);
		j++;
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	if (!pid)
		return (1);
	message = argv[2];
	send_message(pid, message);
	ft_printf("\n");
}

// sleep(2);
// kill(pid, SIGUSR1);
// ft_printf("SIGUSR1 = 0\n");
// usleep(50);

// kill(pid, SIGUSR2);
// ft_printf("SIGUSR2 = 1\n");
// usleep(50);

// kill(pid, SIGUSR2);
// ft_printf("SIGUSR2 = 1\n");
// usleep(50);

// kill(pid, SIGUSR1);
// ft_printf("SIGUSR1 = 0\n");
// usleep(50);

// kill(pid, SIGUSR1);
// ft_printf("SIGUSR1 = 0\n");
// usleep(50);

// kill(pid, SIGUSR1);
// ft_printf("SIGUSR1 = 0\n");
// usleep(50);

// kill(pid, SIGUSR1);
// ft_printf("SIGUSR1 = 0\n");
// usleep(50);

// kill(pid, SIGUSR2);
// ft_printf("SIGUSR2 = 1\n");
// usleep(50);