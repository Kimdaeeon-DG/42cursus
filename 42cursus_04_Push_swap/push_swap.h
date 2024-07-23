/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:50:34 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/23 16:52:28 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	int				data;
	int				index;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_deque
{
	int				size;
	struct s_node	*top;
	struct s_node	*bottom;
}	t_deque;

t_deque	*deque_init(void);
t_node	*getnode(int data);
void	print_error(int type);
void	sort(t_deque *a, t_deque *b);
void	push_top(t_deque *list, int data);
void	pop_top(t_deque *list);
void	push_bottom(t_deque *list, int data);
void	pop_bottom(t_deque *list);
void	sa(t_deque *a);
void	sb(t_deque *b);
void	ss(t_deque *a, t_deque *b);
void	pa(t_deque *a, t_deque *b);
void	pb(t_deque *a, t_deque *b);
void	ra(t_deque *a);
void	rb(t_deque *b);
void	rr(t_deque *a, t_deque *b);
void	rra(t_deque *a);
void	rrb(t_deque *b);
void	rrr(t_deque *a, t_deque *b);
int		check_same_value(int value, t_deque *a);
void	insert_index(int data, int index, t_deque *a);
void	bubble_sort(int *str, t_deque*a);
void	indexing(int size, t_deque *a);
void	insert_value(char**av, t_deque *a);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
void	ft_isdigit(char *c);
size_t	ft_strlen(const char *c);
#endif
