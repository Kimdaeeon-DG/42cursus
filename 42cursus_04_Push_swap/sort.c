#include "push_swap"

int pivot(t_deque *list, int num)
{
	int		*arr;
	int		pi[4];
	int		i;
	t_node	*now;

	arr = (int *)malloc(sizeof(int) * list->size);
	i = 0;
	now = list->top;
	while (i < list->size)
	{
		arr[i] = now->data;
		now = now->prev;
		i++;
	}
	quick(0, i - 1, arr);
	pi[0] = (arr[(i-1)/5]);
	pi[1] = (arr[(((i-1)/5)*2)];
	pi[2] = (arr[(((i-1)/5)*3)];
	pi[3] = (arr[(((i-1)/5)*4)];
	free(arr);
	return (pi[num]);
}
