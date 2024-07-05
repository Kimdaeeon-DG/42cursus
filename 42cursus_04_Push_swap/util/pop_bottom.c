/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_bottom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:02:03 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 15:02:32 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pop_bottom(t_deque *list)
{
	t_node	*nowbottom;
	t_node	*newbottom;

	nowbottom = list->bottom;
	if (nowbottom == NULL)
		return ;
	else if (list->size == 1)
	{
		list->top = NULL;
		list->bottom = NULL;
	}
	else
	{
		newbottom = list->bottom->next;
		newbottom->prev = NULL;
		list->bottom = newbottom;
	}
	list->size--;
	free (nowbottom);
}
