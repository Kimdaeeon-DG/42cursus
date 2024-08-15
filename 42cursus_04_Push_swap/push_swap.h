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
# include <stdio.h>

typedef struct s_node
{
	int				data;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_deque
{
	int		size;
	t_node	*top;
	t_node	*bottom;
}	t_deque;

t_node	*getnode(int data);
void	init_deque(t_deque *b, int **sorted);
int		find_index(int *arr, int data, int size);
t_node	*make_node(t_deque *deque, int *arrays[], int size, int i);
void	insert_index(int data, int index, t_deque *a);
void	make_deque_a(t_deque *deque, int *arr, int *sorted, int size);
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
void	insert_index(int data, int index, t_deque *a);
void	check_duplication(int *unordered, int size);
int		check_num1(const char *str);
int		check_num2(const char *str);
void	check_num(char *num, char **temp, int *nums_count);
int		get_nums_count(char **av);
void	bubble_sort(int *arr, int size);
int		*copy_sorted(int *arr, int size);
int		is_sorted(int *arr, int size);
int		*get_nums(int nums_count, char **av);
int		check_args(int argc, char **argv);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *c);
void	sort2(int *array, int *sorted);
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
void	ft_free(int *array, int *sorted, int flag);
void	free_and_exit(char **matrix, int size, int flag);
void	free_list_and_exit(t_deque *deque, int *arrays[], int i);
int		get_matrix_size(char **matrix);
void	free_matrix(char **matrix, int size);
void	free_all(t_deque *a, t_deque *b, int *a1, int *a2);
#endif
