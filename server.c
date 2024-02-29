/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:21:30 by blackrider        #+#    #+#             */
/*   Updated: 2024/02/29 10:07:18 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clientserver.h"

t_llist	*g_ll = NULL;

void	usrsighand(int signum, siginfo_t *si)
{
	int			counter;
	t_llist		*tmp;

	tmp = findpid(g_ll, si->si_pid);
	if (!tmp)
		tmp = llistadd_back(&g_ll, llistnewnode(newcsd(si->si_pid, "")));
	counter = ++((t_csd *)tmp->data)->counter;
	if (signum == SIGUSR1)
		((t_csd *)(tmp->data))->chr |= 1;
	if (!(counter % BYTESIZE))
	{
		((t_csd *)(tmp->data))->msg = ft_straddchrfree(
				((t_csd *)(tmp->data))->msg, ((t_csd *)(tmp->data))->chr);
		if (!((t_csd *)(tmp->data))->chr)
		{
			ft_printf("%s\n", ((t_csd *)(tmp->data))->msg);
			g_ll = llistdelnode(&tmp, delcsd);
		}
		else
			((t_csd *)(tmp->data))->chr = 0;
	}
	else
		((t_csd *)(tmp->data))->chr <<= 1;
	if (kill(si->si_pid, SIGUSR1))
		errorhand(0, "ERROR kill()!!!");
}

void	sighandler(int signum, siginfo_t *si, void *unctx)
{
	if (signum != SIGUSR1 && signum != SIGUSR2)
	{
		llistclear(&g_ll, delcsd);
		errorhand(-1, "The Server has bin forced shut down");
	}
	usrsighand(signum, si);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sighandler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
		return (errorhand(-1, "ERROR sigaction()!!!"));
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		return (errorhand(-1, "ERROR sigaction()!!!"));
	ft_printf("%d\n", getpid());
	while (1)
		pause();
	return (0);
}
