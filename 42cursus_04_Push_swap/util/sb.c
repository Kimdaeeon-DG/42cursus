/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:48:51 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 17:28:54 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sb(t_deque *b)
{
	int	tmp;

	if (b->size < 2)
		return ;
	tmp = a->top->data;
	a->top->data = a->top->prev->data;
	a->top->prev->data = tmp;
	write(1, "sb\n", 3);
}
