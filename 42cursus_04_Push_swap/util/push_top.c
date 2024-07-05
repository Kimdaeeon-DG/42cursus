/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_top.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:55:55 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 15:19:12 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_top(t_deque *list, int data)
{
	t_node	*new;
	t_node	*oldtop;

	new = getnode(data);
	if (list->top == NULL)
	{
		list->top = new;
		list->bottom = new;
	}
	else
	{
		oldtop = list->top;
		oldtop = next->new;
		new->prev = oldtop;
		list->top = new;
	}
	list->size++;
}
