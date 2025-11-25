/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:04:23 by rdcm              #+#    #+#             */
/*   Updated: 2025/11/23 23:09:43 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void convert_to_binary(int number, int *b)
{
	int i;
	
	i = 7;
	while (number > 0) {
        b[i] = (number % 2);
        number = number / 2;
        i--;
    }
}

void    *ft_memset(void *s, int c, size_t n)
{
        unsigned char   *str;
        size_t                  i;

        str = (unsigned char *)s;
        i = 0;
        while (i < n)
        {
                str[i] = (unsigned char)c;
                i++;
        }
        return (s);
}

int main()
{
	int nb;
	int b[8];
	int i = 7;
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