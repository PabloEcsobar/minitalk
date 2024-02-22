/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientserver.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:58 by blackrider        #+#    #+#             */
/*   Updated: 2024/02/22 15:19:34 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "libft/libft.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define	BYTESIZE	8

typedef struct	s_data
{
	int		pid;
	int		counter;
	char	*msg;
}				t_csd;

t_llist*	findpid(t_llist *llst, int pid);
t_csd		*newcsd(int pid, char *str);
void		delcsd(void *data);