/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:07:35 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/30 22:53:00 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "push_swap.h"

void	print_error(int type) // 에러 출력 함수
{
	if (type >= 1)
		write(2, "Error\n", 6);
	printf("!!");
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

	i = -1;
	size = a->size;
	temp = a->top->index;
	while (++i < size)
	{
		if (temp <= a->top->index)
			pb(a,b);
		else
			ra(a);
	}
}
	
void	atob(t_deque *a, t_deque *b, int n)
{
	int	a_size;
	int pivot1;
	int pivot2;

	a_size = a->size;
	pivot1 = n + a_size / 3;
	pivot2 = n + a_size / 3 * 2;
	if (a_size <= 5)
		return ;
	while (a_size--)
	{
		if (a->top->data <= pivot1)
		{
			pb(a, b);
			rb(b);
		}
		else if (a->top->data <= pivot2)
			pb(a, b);
		else
			ra(a);

	}
	atob(a, b, pivot2);
}

//void	sort_3(t_deque *a)


int	main(int ac, char **av)
{
	t_deque	*a;
	t_deque	*b;

	if (ac < 2)
		return (0);
	a = deque_init(); // deque 생성
	b = deque_init(); // deque 생성
	insert_value(av, a); // 인자를 deque에 넣음

	atob(a, b, 0);
	print_node(a);
//free_deque(a);
//free_deque(b);
	return (0);
}
