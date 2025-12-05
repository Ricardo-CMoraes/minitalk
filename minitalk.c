/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:04:23 by rdcm              #+#    #+#             */
/*   Updated: 2025/12/04 21:17:14 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

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

void ft_print_binary(char *b)
{
	int j;
	
	j = 0;
	printf("Binary: ");
	while (j < 8)
	{
		printf("%d", b[j]);
		j++;
	}
}

int	main(int argc, char **argv)
{
	int		nb;
	char	*b;
	int		i;
	char	*name = "Ricardo";

	nb = ft_atoi(argv[1]);
	if (nb < 0 )
	i = 0;
	while (name[i] != '\0')
	{
		printf("Caracter: %c	", name[i]);
		b = convert_to_binary(name[i]);
		ft_print_binary(b);
		printf("	Valor: %c	Dec: %d\n", convert_to_integer(b), convert_to_integer(b));
		i++;
	}
	return (0);
}
