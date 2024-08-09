/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:50:34 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/09 18:30:25 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	int				data;
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
int		ft_atoi(const char *str, int *flag);
int		ft_isdigit(char *c);
size_t	ft_strlen(const char *c);
void	sort2(t_deque *a);
void	sort3(t_deque *a);
void	sort4(t_deque *a, t_deque *b, int size);
void	sort5(t_deque *a, t_deque *b, int size);
void	sort35(int size, t_deque *a, t_deque *b);
void	max_push_b(t_node *node, t_deque *a, int size);
void	max_push_a(t_node *node, t_deque *b, int size);
void	sort_deque(t_deque *a, t_deque *b);
void	sandglass(t_deque *a, t_deque *b, int chunk);
void	algorithm(t_deque *a, t_deque *b, int size);
void	print_error(int type);
void	free_and_error(t_deque *a, int type);
void	free_matrix(char **matrix);
void	free_all(t_deque *a, t_deque *b);
#endif
