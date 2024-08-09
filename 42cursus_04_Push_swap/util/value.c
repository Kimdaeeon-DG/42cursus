/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:57:11 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/09 18:28:48 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	check_same_value(int value, t_deque *a)
{
	t_node	*n;

	n = a->bottom;
	while (n != NULL)
	{
		if (n->data == value)
			return (1);
		n = n->next;
	}
	return (0);
}

void	insert_index(int data, int index, t_deque *a)
{
	t_node	*cnt;

	cnt = a->bottom;
	while (cnt != NULL)
	{
		if (cnt->data == data)
		{
			cnt->data = index;
			return ;
		}
		cnt = cnt->next;
	}
}

void	bubble_sort(int *str, t_deque *a)
{
	int	i;
	int	j;
	int	temp;
	int	checker;

	i = -1;
	checker = 0;
	while (++i < a->size - 1)
	{
		j = -1;
		while (++j < a->size - i - 1)
		{
			if (str[j] > str[j + 1])
			{
				temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
				checker++;
			}
		}
	}
	if (checker == 0)
		free_and_error(a, -1);
}

void	indexing(int size, t_deque *a)
{
	int		i;
	int		*str;	
	t_node	*node;

	str = (int *)malloc(sizeof(int) * size);
	if (!str)
		return ;
	node = a->bottom;
	i = -1;
	while (node != NULL)
	{
		str[++i] = node->data;
		node = node->next;
	}
	bubble_sort(str, a);
	i = -1;
	while (++i < a->size)
		insert_index(str[i], i, a);
	free(str);
}

void	insert_value(char **av, t_deque *a)
{
	int		i;
	int		j;
	int		value;
	int		flag;
	char	**arr;

	i = 0;
	flag = 0;
	while (av[++i])
	{
		arr = ft_split(av[i], ' ');
		j = 0;
		while (arr[j])
		{
			value = ft_atoi(arr[j], &flag);
			if (flag || ft_isdigit(arr[j]) || check_same_value(value, a))
			{
				free_matrix(arr);
				free_and_error(a, 1);
			}
			push_top(a, ft_atoi(arr[j++], &flag));
		}
	}
	free_matrix(arr);
	indexing(a->size, a);
}
