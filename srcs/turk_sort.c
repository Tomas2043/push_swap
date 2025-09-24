/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:27:03 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/24 10:40:12 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	find_position(t_stack *stack, int value)
{
	t_node	*cur;
	int		pos;

	cur = stack->top;
	pos = 0;
	while (cur)
	{
		if (cur->next == value)
			return (pos);
		cur = cur->next;
		pos++;
	}
	return (-1);
}

static int	find_min_value(t_stack  *stack)
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

static int	find_max_value(t_stack *stack)
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

static int	find_bigger_target(t_stack *a, int b_value)
{
	t_node	*cur;
	int		pos;
	int		target_pos;
	int		min_bigger;

	cur = a->top;
	pos = 0;
	target_pos = 0;
	min_bigger = INT_MAX;
	while (cur)
	{
		if (cur->value > b_value && cur->value < min_bigger)
		{
			min_bigger = cur->value;
			target_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	return (target_pos);
}
