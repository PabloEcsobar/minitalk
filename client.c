/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:19:03 by blackrider        #+#    #+#             */
/*   Updated: 2024/02/24 14:49:07 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clientserver.h"

int		g_gotanswear = 0;

void	sendchar(int serverpid, char ch)
{
	int			i;
	t_uchar		mask;

	i = 0;
	mask = 128;
	while (i < BYTESIZE)
	{
		if (mask & (ch << i))
		{
			if (kill(serverpid, SIGUSR1))
				errorhand(-1, "ERROR!!!Perhaps bad PID");
		}
		else
		{
			if (kill(serverpid, SIGUSR2))
				errorhand(-1, "ERROR!!!Perhaps bad PID");
		}
		while (!g_gotanswear)
			emptyft();
		++i;
		g_gotanswear = 0;
	}
}

void	senddata(int serverpid, char *data)
{
	while (*data)
	{
		sendchar(serverpid, *data);
		++data;
	}
	sendchar(serverpid, '\0');
}

static void	sighandler(int signum)
{
	if (signum != SIGUSR1)
		exit(-1);
	g_gotanswear = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
		return (errorhand(-1, "ERROR!!! Bad clients arguments"));
	sa.sa_handler = sighandler;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
		return (errorhand(-1, "ERROR sigaction()!!!"));
	senddata(ft_atoi(argv[1]), argv[2]);
	return (0);
}
