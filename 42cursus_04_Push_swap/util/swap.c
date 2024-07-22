/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:35:22 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/22 10:40:25 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sa(t_deque *a)
{
	int	tmp;

	if (a->size < 2)
		return ;
	tmp = a->top->data;
	a->top->data = a->top->prev->data;
	a->top->prev->data = tmp;
	write(1, "sa\n", 3);
}

void	sb(t_deque *b)
{
	int	tmp;

	if (b->size < 2)
		return ;
	tmp = b->top->data;
	b->top->data = b->top->prev->data;
	b->top->prev->data = tmp;
	write(1, "sb\n", 3);
}

void	ss(t_deque *a, t_deque *b)
{
	int	tmp;

	if (a->size < 2 || b->size < 2)
		return ;
	tmp = a->top->data;
	a->top->data = a->top->prev->data;
	a->top->prev->data = tmp;
	tmp = b->top->data;
	b->top->data = b->top->prev->data;
	b->top->prev->data = tmp;
	write(1, "ss\n", 3);
}