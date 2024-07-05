/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:47:15 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 15:15:09 by daeekim          ###   ########.fr       */
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
