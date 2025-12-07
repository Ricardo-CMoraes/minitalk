/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:58:06 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/07 19:55:52 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_bits(pid_t pid, char i)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((i >> bit) & 1)
			my_kill(pid, SIGUSR2);
		else
			my_kill(pid, SIGUSR1);
		usleep(UWAIT);
		bit--;
	}
}

void	send_message(pid_t pid, const char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		ft_send_bits(pid, message[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t		pid;
	char		*message;

	if (argc != 3)
		handle_error("Error: more or less than three arguments\n");
	pid = ft_atoi(argv[1]);
	if (!(pid > 0))
		handle_error("Error: wrong pid\n");
	message = argv[2];
	send_message(pid, message);
	send_message(pid, "\n");
	return (0);
}
