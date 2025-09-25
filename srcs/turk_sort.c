/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:27:03 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/25 10:37:57 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	find_position(t_stack *stack, int value)
{
	t_node	*cur;
	int		pos;

	cur = stack->top;
	pos = 0;
	while (cur)
	{
		if (cur->next->value == value)
			return (pos);
		cur = cur->next;
		pos++;
	}
	return (-1);
}

int	find_min_value(t_stack  *stack)
{
	t_node	*cur;
	int		min_val;

	if (!stack || !stack->top)
		return (0);
	min_val = stack->top->value;
	cur = stack->top->next;
	while (cur)
	{
		if (cur->value < min_val)
			min_val = cur->value;
		cur = cur->next;
	}
	return (min_val);
}

int	find_max_value(t_stack *stack)
{
	t_node	*cur;
	int		max_val;

	if (!stack || !stack->top)
		return (0);
	max_val = stack->top->value;
	cur = stack->top->next;
	while (cur)
	{
		if (cur->value > max_val)
			max_val = cur->value;
		cur = cur->next;
	}
	return (max_val);
}

void	push_initial_to_b(t_stack *a, t_stack *b)
{
	int	push_count;

	if (a->size <= 5)
		return ;
	push_count = a->size - 3;
	while (push_count-- && a->size > 3)
		pb(a, b);
	sort3(a);
}

void	turk_sort(t_stack *a, t_stack *b)
{
	int	min_pos;

	if (a->size <= 5)
	{
		if (a->size <= 3)
			sort3(a);
		else
			sort5(a, b);
		return ;
	}
	push_initial_to_b(a, b);
	while (b->size > 0)
		push_cheapest_to_a(a, b);
	min_pos = find_position(a, find_min_value(a));
	rotate_to_position_a(a, min_pos);
}
