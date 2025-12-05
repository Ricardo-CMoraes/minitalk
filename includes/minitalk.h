/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdcm <rdcm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:58:13 by rida-cos          #+#    #+#             */
/*   Updated: 2025/12/04 23:13:29 by rdcm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# define UWAIT 300

int		convert_to_integer(char	*b);
void	handle_error(const char *msg);
void	send_bit(int pid, int signal);

#endif
