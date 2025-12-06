/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:53:52 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/05 23:03:08 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		binary = convert_to_binary(message[j]);
		i = 0;
		while (i < 8)
		{
			if (binary[i] == 0)
				send_bit(pid, SIGUSR1);
			else
				send_bit(pid, SIGUSR2);
			i++;
		}
		free(binary);
		j++;
	}
	i = 0;
	while (i++ < 8)
		send_bit(pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
		handle_error("Error: more or less than three arguments\n");
	pid = ft_atoi(argv[1]);
	if (!(pid > 0))
		handle_error("Error: wrong pid\n");
	message = argv[2];
	send_message(pid, message);
	return (0);
}
