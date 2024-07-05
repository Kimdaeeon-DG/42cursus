/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_bottom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:00:57 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 15:01:56 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_bottom(t_deque *list, int data)
{
	t_node	*new;
	t_node	*oldbottom;

	new = getnode(data);
	if (list->bottom == NULL)
	{
		list->top = new;
		list->bottom = new;
	}
	else
	{
		oldbottom = list->bottom;
		oldbottom->prev = new;
		new->next = oldbottom;
		list->bottom = new;
	}
	list->size++;
}
