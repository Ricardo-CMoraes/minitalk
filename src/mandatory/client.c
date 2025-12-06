/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:58:06 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/06 19:03:17 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((i >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(UWAIT);
		bit--;
	}
}

void	send_message(int pid, char *message)
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
