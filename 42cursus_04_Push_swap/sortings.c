/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:50:19 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/09 16:50:21 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort2(t_deque *a)
{
	sa(a);
}

void	sort3(t_deque *a)
{
	int	arr[3];

	arr[0] = a->bottom->data;
	arr[1] = a->bottom->next->data;
	arr[2] = a->bottom->next->next->data;
	if (arr[0] == 0 && arr[1] == 2)
	{
		rra(a);
		sa(a);
	}
	else if (arr[0] == 0 && arr[1] == 1)
		return ;
	else if (arr[0] == 1 && arr[1] == 0)
		sa(a);
	else if (arr[0] == 1 && arr[1] == 2)
		rra(a);
	else if (arr[0] == 2 && arr[1] == 0)
		ra(a);
	else if (arr[0] == 2 && arr[1] == 1)
	{
		sa(a);
		rra(a);
	}
}

void	sort4(t_deque *a, t_deque *b, int size)
{
	t_node	*node;

	node = a->bottom;
	max_push_b(node, a, size);
	pb(a, b);
	sort3(a);
	pa(a, b);
	ra(a);
}

void	sort5(t_deque *a, t_deque *b, int size)
{
	t_node	*node;

	node = a->bottom;
	max_push_b(node, a, size);
	pb(a, b);
	node = a->bottom;
	max_push_b(node, a, size - 1);
	pb(a, b);
	sort3(a);
	pa(a, b);
	ra(a);
	pa(a, b);
	ra(a);
}

void	sort35(int size, t_deque *a, t_deque *b)
{
	if (size == 3)
		sort3(a);
	else if (size == 4)
		sort4(a, b, size);
	else
		sort5(a, b, size);
}
