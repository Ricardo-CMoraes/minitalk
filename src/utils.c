/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:56:37 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/05 21:31:57 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	convert_to_integer(char	*b)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 128;
	nb = 0;
	while (i < 8)
	{
		nb = j * b[i] + nb;
		i++;
		j = j / 2;
	}
	return (nb);
}

void	handle_error(const char *msg)
{
	ft_printf(msg);
	exit(EXIT_FAILURE);
}

void	send_bit(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		handle_error("Error: process does not exist\n");
	usleep(UWAIT);
}
