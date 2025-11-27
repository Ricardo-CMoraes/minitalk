/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:04:23 by rdcm              #+#    #+#             */
/*   Updated: 2025/11/26 23:15:35 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int	convert_to_integer(int	*b)
{
	int	i;
	int j;
	int	nb;
	
	i = 0;
	j = 128; //1 2 4 8 16 32 64 128
	nb = 0;
	while (i < 8)
	{
		nb = j * b[i] + nb;
		//printf("j:%d e i:%d e nb:%d\n", j, i, nb);
		i++;
		j = j / 2;
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

int     ft_atoi(const char *str)
{
        int     sign;
        int     nb;
        int     i;

        i = 0;
        sign = 1;
        nb = 0;
        while (str[i] == ' ' || ((str[i] >= 9) && (str[i] <= 13)))
                i++;
        if ((str[i] == '-') || (str[i] == '+'))
        {
                if (str[i] == '-')
                        sign = -1;
                i++;
                if (str[i] == '-' || str[i] == '+')
                        return (0);
        }
        while ((str[i] >= '0') && (str[i] <= '9'))
        {
                nb = (nb * 10) + (str[i] - '0');
                i++;
        }
        return (nb * sign);
}

int	main(int argc, char **argv)
{
	int	nb;
	int	b[8];
	int	i = 7;

	nb = ft_atoi(argv[1]);
	ft_memset(b, 0, sizeof(b));
	convert_to_binary(nb, b);
	printf("\n\n");
	int j = 0;
	while (j < 8)
	{
		printf("%d", b[j]);
		j++;
	}
	printf("\n");
	printf("\nValor: %d\n", convert_to_integer(b));
	return (0);
}