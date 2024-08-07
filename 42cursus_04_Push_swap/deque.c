/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:33:41 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/30 22:51:24 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_deque	*deque_init(void)
{
	t_deque	*deque;

	deque = malloc(sizeof(t_deque));
	if (deque == NULL)
		return (0);
	deque->top = NULL;
	deque->bottom = NULL;
	deque->size = 0;
	return (deque);
}

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
