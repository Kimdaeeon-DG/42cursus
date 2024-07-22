/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:57:11 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/22 14:59:29 by daeekim          ###   ########.fr       */
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

void insert_index(int data, int index, t_deque *a) // 특정 노드를 찾음
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

void	indexing(int *str, t_deque *a) // 인덱스 넣음
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < a->size - 1) // 버블 정렬
	{
		j = 0;
		while (j < a->size - i - 1)
		{
			if (str[j] > str[j+1])
			{
				temp = str[j];
				str[j] = str[j+1];
				str[j+1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < a->size) // 정렬된 순서 바탕으로 인덱스를 넣음
	{
		insert_index(str[i], i + 1, a);
		i++;
	}
}

void insert_value(int ac, char **av, t_deque *a) // deque에 값과 인덱스를 넣음
{
	int		i;
	int		j;
	int		count;
	int		str[ac +9];
	char	**arr;

	i = 0;
	count = 0;
	while (av[++i])
	{
		arr = ft_split(av[i], ' '); // split으로 문자열을 쪼개줌
		j = 0;
		while (arr[j])
		{ 
			ft_isdigit(arr[j]); // 정수가 아니면 에러 출력
			check_same_value(ft_atoi(arr[j]), a); // 같은 값이 있으면 에러 출력
			str[count++] = ft_atoi(arr[j]); // 배열에 값을 넣음 
			push_bottom(a, ft_atoi(arr[j++])); // deque에 값을 넣음
		}
	}
	indexing(str, a);
}
