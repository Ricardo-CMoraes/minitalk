/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:58:13 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/06 11:23:58 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# define UWAIT 375

int		convert_to_integer(char	*b);
void	handle_error(const char *msg);
void	send_bit_and_wait(int pid, int signal);

#endif
