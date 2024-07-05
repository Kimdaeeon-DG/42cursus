/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:53:33 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 15:15:27 by daeekim          ###   ########.fr       */
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
