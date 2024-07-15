/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:50:17 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/15 20:54:35 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_bottom(t_deque *list, int data)
{
	t_node	*new_node;
	t_node	*cnt_bottom;

	new_node = getnode(data);
	if (list->bottom == NULL)
	{
		list->top = new_node;
		list->bottom = new_node;
	}
	else
	{
		cnt_bottom = list->bottom;
		cnt_bottom->prev = new_node;
		new_node->next = cnt_bottom;
		list->bottom = new_node;
	}
	list->size++;
}

void	push_top(t_deque *list, int data)
{
	t_node	*new_node;
	t_node	*cnt_top;

	new_node = getnode(data);
	if (list->top == NULL)
	{
		list->top = new_node;
		list->bottom = new_node;
	}
	else
	{
		cnt_top = list->top;
		cnt_top->next = new_node;
		new_node->prev = cnt_top;
		list->top = new_node;
	}
	list->size++;
}

void	pop_bottom(t_deque *list)
{
	t_node	*cnt_bottom;
	t_node	*new_bottom;

	cnt_bottom = list->bottom;
	if (cnt_bottom == NULL)
		return ;
	else if (list->size == 1)
	{
		list->top = NULL;
		list->bottom = NULL;
	}
	else
	{
		new_bottom = list->bottom->next;
		new_bottom->prev = NULL;
		list->bottom = new_bottom;
	}
	list->size--;
	free (cnt_bottom);
}

void	pop_top(t_deque *list)
{
	t_node	*cnt_top;
	t_node	*new_top;

	cnt_top = list->top;
	if (cnt_top == NULL)
		return ;
	else if (list->size == 1)
	{
		list->top = NULL;
		list->bottom = NULL;
	}
	else
	{
		new_top = list->top->prev;
		new_top->next = NULL;
		list->top = new_top;
	}
	list->size--;
	free (cnt_top);
}
