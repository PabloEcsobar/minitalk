/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientserver.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:58 by blackrider        #+#    #+#             */
/*   Updated: 2024/02/23 17:05:57 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ft_printf/libft/libft.h"
#include "ft_printf/headers/ft_printf_bonus.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define	BYTESIZE	8

typedef unsigned char	uchar;
typedef struct	s_data_client
{
	int		pid;
	int		counter;
	char	chr;
	char	*msg;
}				t_csd;

t_llist*	findpid(t_llist *llst, int pid);
t_csd		*newcsd(int pid, char *str);
void		delcsd(void *data);
void		emptyft(void);