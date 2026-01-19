/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:17:25 by toandrad          #+#    #+#             */
/*   Updated: 2025/12/16 10:56:07 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	find_bigger_target(t_stack *a, int b_value)
{
	t_node	*cur;
	int		pos;
	int		target_pos;
	int		min_bigger;

	cur = a->top;
	pos = 0;
	target_pos = -1;
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

int	find_target_pos_in_a(t_stack *a, int b_value)
{
	int	target_pos;
	int	max_value;
	int	max_pos;

	if (a->size == 0)
		return (0);
	target_pos = find_bigger_target(a, b_value);
	if (target_pos != -1)
		return (target_pos);
	max_value = find_max_value(a);
	max_pos = find_position(a, max_value);
	return ((max_pos + 1) % a->size);
}

int	get_b_value_at_index(t_stack *b, int index)
{
	t_node	*cur;
	int		i;

	cur = b->top;
	i = 0;
	while (cur && i < index)
	{
		cur = cur->next;
		i++;
	}
	if (!cur)
		return (INT_MAX);
	return (cur->value);
}

int	find_cheapest_index(t_stack *a, t_stack *b)
{
	int	cheapest_cost;
	int	cheapest_index;
	int	current_cost;
	int	i;

	cheapest_cost = INT_MAX;
	cheapest_index = 0;
	i = 0;
	while (i < b->size)
	{
		current_cost = calculate_cost(a, b, i);
		if (current_cost < cheapest_cost)
		{
			cheapest_cost = current_cost;
			cheapest_index = i;
		}
		i++;
	}
	return (cheapest_index);
}

void	push_cheapest_to_a(t_stack *a, t_stack *b)
{
	int	cheapest_index;
	int	b_value;
	int	target_pos;

	cheapest_index = find_cheapest_index(a, b);
	b_value = get_b_value_at_index(b, cheapest_index);
	target_pos = find_target_pos_in_a(a, b_value);
	execute_moves(a, b, target_pos, cheapest_index);
	pa(a, b);
}
