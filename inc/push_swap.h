/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:10:57 by toandrad          #+#    #+#             */
/*   Updated: 2026/01/20 13:17:15 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <limits.h>

typedef struct s_node
{
	int						value;
	struct s_node			*prev;
	struct s_node			*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}	t_stack;

t_node	*stack_pop_top(t_stack *stack);
t_node	*stack_pop_bottom(t_stack *stack);
void	stack_push_top(t_stack *stack, t_node *node);
void	stack_push_bottom(t_stack *stack, t_node *node);

void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);

void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);

void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

void	sort3(t_stack *a);
void	sort5(t_stack *a, t_stack *b);

void	stack_init(t_stack *s);
t_node	*node_new(int v);
void	free_stack(t_stack *s);
int		error_exit(t_stack *a, t_stack *b);

int		is_sorted(t_stack *a);

int		parse_args(int ac, char **av, t_stack *a);

void	turk_sort(t_stack *a, t_stack *b);
void	push_initial_to_b(t_stack *a, t_stack *b);
void	push_cheapest_to_a(t_stack *a, t_stack *b);
void	rotate_to_position_a(t_stack *a, int pos);
void	rotate_to_position_b(t_stack *b, int pos);
int		find_position(t_stack *stack, int value);
int		find_min_value(t_stack *stack);
int		find_max_value(t_stack *stack);
int		find_target_pos_in_a(t_stack *a, int b_value);
int		find_cheapest_index(t_stack *a, t_stack *b);
int		calculate_cost(t_stack *a, t_stack *b, int b_index);
int		get_b_value_at_index(t_stack *b, int index);
void	execute_moves(t_stack *a, t_stack *b, int tpos, int cidx);

#endif
