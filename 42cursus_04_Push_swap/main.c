/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:07:35 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/16 17:43:32 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "push_swap.h"

void print_error(int type)
{
	if (type >= 1)
		write(2, "Error\n", 6);
	exit(1);
}

void print_node(t_deque *a)
{
	t_node	*pnt;

	pnt = a->top;
	while (pnt != NULL)
	{
		printf("%d\n", pnt->data);
		pnt = pnt->prev;
	}
}

int check_same_value(int value, t_deque *a)
{
	t_node	*n;

	n = a->bottom;
	while (n != NULL)
	{
		if (n->data == value)
			print_error(1);
		n = n->next;
	}
	return (1);
}

void insert_value(char **av, t_deque *a)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	while (av[++i])
	{
		arr = ft_split(av[i], ' ');
		j = 0;
		while (arr[j])
		{
			if (!ft_isdigit(arr[j]))
				print_error(1);
			if (check_same_value(ft_atoi(arr[j]), a))
				push_bottom(a, ft_atoi(arr[j++]));
		}
	}
}
	
int	main(int ac, char **av)
{
	t_deque	*a;
	t_deque	*b;

	if (ac < 2)
		return (0);
	a = deque_init();
	b = deque_init();
	insert_value(av, a);
	pb(a,b);
	print_node(a);
	print_node(b);

//free_deque(a);
//free_deque(b);
	return (0);
}
