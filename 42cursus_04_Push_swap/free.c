/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:55:29 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/14 18:44:09 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free(int *array, int *sorted, int flag)
{
	free(array);
	free(sorted);
	print_error(flag);
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

void	free_and_exit(char **matrix, int size, int flag)
{
	free_matrix(matrix, size);
	print_error(flag);
}

void	free_matrix(char **matrix, int size)
{
	--size;
	while (size >= 0)
	{
		free(matrix[size]);
		matrix[size] = NULL;
		--size;
	}
	free(matrix);
	matrix = NULL;
}

void	free_all(t_deque *a, t_deque *b, int *a1, int *a2)
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
		while (++i < a->size)
		{
			temp = a->bottom;
			a->bottom = a->bottom->next;
			free(temp);
		}
	}
	free(a1);
	free(a2);
}
