/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:07:35 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/23 17:48:13 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "push_swap.h"

void print_error(int type) // 에러 출력 함수
{
	if (type >= 1)
		write(2, "Error\n", 6);
	exit(1);
}

void print_node(t_deque *a) // 값 확인용 출력 함수
{
	t_node	*pnt;

	pnt = a->top;
	while (pnt != NULL)
	{
		printf("data: %d\n", pnt->data);
		printf("index: %d\n", pnt->index);
		pnt = pnt->prev;
	}
}

void free_deque(int ac, t_deque *a)
{
	int	i;

	i = 1;
	while (i++ < ac)
		pop_bottom(a);
}

void	sort(t_deque *a, t_deque *b)
{
	int	i;
	int	size; 
	int temp;

	i = 0;
	size = a->size;
	temp = a->top->data;
	while (++i < size)
	{
		if (temp < a->top->data)
			pb(a,b);
		else
			ra(a);
	}
}
	
int	main(int ac, char **av)
{
	t_deque	*a;
	t_deque	*b;

	if (ac < 2)
		return (0);
	a = deque_init(); // deque 생성
	b = deque_init(); // deque 생성
	insert_value(av, a); // 인자를 deque에 넣음
	print_node(a);
	printf("\n");

	//sort(a, b);
	ra(a);
	ra(a);
	printf("a:\n");
	print_node(a);
	printf("b:\n");
	print_node(b);
//free_deque(a);
//free_deque(b);
	return (0);
}
