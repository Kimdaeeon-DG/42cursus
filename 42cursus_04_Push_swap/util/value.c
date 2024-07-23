/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:57:11 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/23 17:58:01 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int check_same_value(int value, t_deque *a) // 같은 값 확인
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

void insert_index(int data, int index, t_deque *a) // 특정 노드를 찾아서 인덱스를 넣음
{
    t_node *cnt = a->bottom;
    while (cnt != NULL)
    {
        if (cnt->data == data)
		{
			cnt->index = index;
            return ;
		}
        cnt = cnt->next;
    }
}


void	bubble_sort(int *str, t_deque *a) // data를 정렬함
{
	int	i;
	int	j;
	int	temp;

	i = -1;
	while (++i < a->size - 1) // 버블 정렬
	{
		j = -1;
		while (++j < a->size - i - 1)
		{
			if (str[j] > str[j+1])
			{
				temp = str[j];
				str[j] = str[j+1];
				str[j+1] = temp;
			}
		}
	}
}

void	indexing(int size, t_deque *a) // index를 넣는 함수
{
	int	i;
	int *str;	
	t_node *node;

	str = (int *)malloc(sizeof(int) * size); // data를 담을 저장공간 할당
	if (!str) // 예외처리
		return;
	node = a->bottom; // node를 바텀으로 설정
	i = 0;
	while (node != NULL) // deque에 담긴 값들을 str에 담아줌
	{
		str[i++] = node->data;
		node = node->next;
	}
	bubble_sort(str, a);
	i = -1;
	while (++i < a->size) // 정렬된 순서 바탕으로 인덱스를 넣음
		insert_index(str[i], i + 1, a);
	free(str);
}

void insert_value(char **av, t_deque *a) // deque에data와 index를 넣는 함수
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	while (av[++i])
	{
		arr = ft_split(av[i], ' '); // split으로 문자열을 쪼개줌
		j = 0;
		while (arr[j])
		{ 
			ft_isdigit(arr[j]); // 정수가 아니면 에러 출력
			check_same_value(ft_atoi(arr[j]), a); // 같은 값이 있으면 에러 출력
			push_bottom(a, ft_atoi(arr[j++])); // deque에 값을 넣음
		}
	}
	indexing(a->size, a); // index를 넣기 위해 indexing함수 호출
}
