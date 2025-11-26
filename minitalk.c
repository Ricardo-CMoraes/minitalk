/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:04:23 by rdcm              #+#    #+#             */
/*   Updated: 2025/11/25 21:13:28 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	expo(int position)
{
	if (expo == 0)
		return (128);
	else if (expo == 1)
		return (64);
	else if (expo == 2)
		return (32);
	else if (expo == 3)
		return (16);
	else if (expo == 4)
		return (8);
	else if (expo == 5)
		return (4);
	else if (expo == 6)
		return (2);
	else if (expo == 7)
		return (0);
}

void	convert_to_binary(int number, int *b)
{
	int	i;

	i = 7;
	while (number > 0)
	{
		b[i] = (number % 2);
		number = number / 2;
		i--;
	}
}

void	convert_to_integer(int number, int	*b)
{
	int	i;
	int	nb;

	i = 0;
	while (i < 8)
	{
		nb = (expo(i)) * b[i] + nb;
		i++;
	}
	return (nb);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

int	main()
{
	int	nb;
	int	b[8];
	int	i = 7;

	nb = 5;
	ft_memset(b, 0, sizeof(b));
	convert_to_binary(nb, b);

	printf("\n\n");

	int j = 0;
	while (j < 8)
	{
		printf("%d\n", b[j]);
		j++;
	}
	return (0);
}