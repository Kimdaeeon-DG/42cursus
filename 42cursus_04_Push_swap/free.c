/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:55:29 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/09 18:28:17 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_error(int type)
{
	if (type >= 1)
		write(2, "Error\n", 6);
	exit(1);
}

void	free_and_error(t_deque *a, int type)
{
	t_node	*temp;
	int		i;

	i = -1;
	while (++i < a->size)
	{
		temp = a->bottom;
		a->bottom = a->bottom->next;
		free(temp);
	}
	free(a);
	if (type != -42)
		print_error(type);
}


void	free_matrix(char **matrix)
{
	int size;

	size = 0;
	while (matrix[size])
		size++;

	while (size >= 0)
	{
		free(matrix[size]);
		matrix[size] = NULL;
		--size;
	}
	free(matrix);
	matrix = NULL;
}

void	free_all(t_deque *a, t_deque *b)
{
	t_node	*temp;
	int		i;

	i = -1;
	while (++i < a->size)
	{
		temp = a->bottom;
		a->bottom = a->bottom->next;
		free(temp);
	}
	if (b->bottom)
	{
		i = -1;
		while (++i < b->size)
		{
			temp = b->bottom;
			b->bottom= b->bottom->next;
			free(temp);
		}
	}
	free(a);
	free(b);
}
