/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_top.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:59:58 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 15:00:46 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pop_top(t_deque *list)
{
	t_node	*nowtop;
	t_node	*newtop;

	nowtop = list->top;
	if (nowtop == NULL)
		return ;
	else if (list->size == 1)
	{
		list->top = NULL;
		list->bottom = NULL;
	}
	else
	{
		newtop = list->top->prev;
		newtop->next = NULL;
		list->top = newtop;
	}
	list->size--;
	free (nowtop);
}
