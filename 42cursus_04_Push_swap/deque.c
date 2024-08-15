/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:33:41 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/13 19:51:17 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*getnode(int data)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (0);
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	init_deque(t_deque *b, int **sorted)
{
	b->bottom = NULL;
	b->top = NULL;
	b->size = 0;
	*sorted = NULL;
}

int	find_index(int *arr, int data, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (arr[i] == data)
			return (i);
	}
	return (0);
}

void	insert_index(int data, int index, t_deque *a)
{
	t_node	*cnt;

	cnt = a->bottom;
	while (cnt != NULL)
	{
		if (cnt->data == data)
		{
			cnt->data = index;
			return ;
		}
		cnt = cnt->next;
	}
}

void	make_deque_a(t_deque *deque, int *array, int *sorted, int size)
{
	int	i;

	deque->top = NULL;
	deque->bottom = NULL;
	deque->size = 0;
	i = -1;
	while (++i < size)
		push_top(deque, array[i]);
	i = -1;
	while (++i < size)
		insert_index(sorted[i], i, deque);
}
