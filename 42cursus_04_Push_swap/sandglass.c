#include "push_swap.h"

void	max_push_b(t_node *node, t_deque *a, int size)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (flag == 0)
	{
		if (node->data == size - 1)
		{
			if (i > size - i - 1)
			{
				while (i++ != size)
					rra(a);
			}
			else
				while (i-- > 0)
					ra(a);
			break ;
		}
		i++;
		node = node->next;
		if (node == a->bottom)
			flag = 1;
	}
}

void	max_push_a(t_node *node, t_deque *b, int size)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (flag == 0)
	{
		if (node->data == size - 1)
		{
			if (i > size - i - 1)
			{
				while (i++ != size)
				rrb(b);
			}
			else
				while (i-- > 0)
					rb(b);
			break ;
		}
		i++;
		node = node->next;
		if (node == b->bottom)
			flag = 1;
	}
}

void	sort_deque(t_deque *a, t_deque *b)
{
	t_node	*node;

	while (b->bottom != NULL)
	{
		node = b->bottom;
		max_push_a(node, b, b->size);
		pa(a, b);
	}
}

void	sandglass(t_deque *a, t_deque *b, int chunk)
{
	int		counter;
	t_node	*node;

	counter = 0;
	node = a->bottom;
	while (a->bottom != NULL)
	{
		if (node->data < counter)
		{
			pb(a, b);
			rb(b);
			counter++;
		}
		else if (node->data < counter + chunk)
		{
			pb(a, b);
			counter++;
		}
		else
			ra(a);
		node = a->bottom;
	}
}

void	algorithm(t_deque *a, t_deque *b, int size)
{
	double	chunk;

	chunk = 0.00000053 * size * size + 0.03 * size + 14.5;
	sandglass(a, b, (int)chunk);
	sort_deque(a, b);
}
