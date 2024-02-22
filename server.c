/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:21:30 by blackrider        #+#    #+#             */
/*   Updated: 2024/02/22 15:21:20 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clientserver.h"

t_llist    *ll_global = NULL;

void    sighandler(int signum, siginfo_t *si, void *unctx)
{
    int     counter;
    char    *msg;
	t_llist	*tmp;

	tmp = findpid(ll_global, si->si_pid);
    msg = ((t_csd *)tmp->data)->msg;
	if (!tmp)
        tmp = llistadd_back(&ll_global, llistnewnode(newcsd(si->si_pid, "")));
    counter = ((t_csd *)tmp->data)->counter;
    if (signum)
		*(msg + counter / BYTESIZE) |= 1;
    if (!(counter % BYTESIZE))
	{
		if (!*msg)
        {
			printf("%s\n", msg);
			llistdelnode(&tmp, delcsd);
        }
		((t_csd *)tmp->data)->msg = ft_strjoinfree(msg, "", 0);
	}
	else
		*(msg + counter / BYTESIZE) <<= 1;
	kill(si->si_pid, SIGUSR1);
}

void    server()
{
    struct sigaction sa;
    
    sa.sa_sigaction = sighandler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    printf("%d\n", getpid());
    while (1)
    {

    }
}

int main(void)
{
    server();
    return (0);
}