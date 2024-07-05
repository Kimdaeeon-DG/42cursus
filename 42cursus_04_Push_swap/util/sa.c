/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:44:26 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 17:28:35 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
