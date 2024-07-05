/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:26:14 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 17:29:53 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_deque *a)
{
	if (a->size < 2)
		return ;
	push_top(a, a->bottom->data);
	pop_bottom(a);
	write(1, "rra\n", 4);
}
