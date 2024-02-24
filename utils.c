/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:54:26 by blackrider        #+#    #+#             */
/*   Updated: 2024/02/23 14:42:59 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clientserver.h"

t_llist	*findpid(t_llist *llst, int pid)
{
	t_llist	*tmp;

	if (!(llst))
		return (NULL);
	tmp = llst->previous;
	while (llst)
	{
		if (((t_csd *)llst->data)->pid == pid)
			return (llst);
		llst = llst->next;
	}
	if (!tmp)
		return (NULL);
	while (tmp->next)
	{
		if (((t_csd *)tmp->data)->pid == pid)
			return (tmp);
		tmp = tmp->previous;
	}
	return (NULL);
}

t_csd	*newcsd(int pid, char *str)
{
	t_csd	*tmp;

	tmp = malloc(sizeof(t_csd));
	if (!tmp)
		return (NULL);
	tmp->pid = pid;
	tmp->counter = 0;
	tmp->chr = 0;
	tmp->msg = ft_strdup(str);
	return (tmp);
}

void	delcsd(void *data)
{
	free(((t_csd *)data)->msg);
	free((t_csd *)data);
}

void	emptyft(void)
{
	return ;
}
