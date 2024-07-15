/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:07:35 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/15 23:20:10 by daeekim          ###   ########.fr       */
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
	t_node *pnt = a->top;
	
	while (pnt != NULL)
	{
		printf("%d\n", pnt->data);
		pnt = pnt->prev;
	}
}

/*
int check_argument(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac - 2)
	{
		if (!isdigit(av[i]) && !isalpha(av[i])) 
	}
}
*/

void insert_value(char **av, t_deque *a)
{
	int		i;
	char	**arr;

	i = 0;
	arr = ft_split(av[1], ' ');
	while (arr[i])
		push_top(a, ft_atoi(arr[i++]));
}

#include <stdlib.h>
	
int	main(int ac, char **av)
{
	t_deque	*a;

	if (ac < 2)
		return (0);
	a = deque_init();
	insert_value(av, a);
	print_node(a);

//	check_argument(ac, av);
//check_string(ac, av);
//check_same(a);
//free_deque(a);
//free_deque(b);
	return (0);
}
