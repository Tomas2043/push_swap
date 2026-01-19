/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:12:51 by toandrad          #+#    #+#             */
/*   Updated: 2025/12/16 11:08:27 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	calculate_rotation_cost(int pos, int size)
{
	if (pos >= size / 2)
		return (pos);
	else
		return (size - pos);
}

int	calculate_cost(t_stack *a, t_stack *b, int b_index)
{
	int	b_value;
	int	target_pos_a;
	int	cost;

	b_value = get_b_value_at_index(b, b_index);
	if (b_value == INT_MAX)
		return (INT_MAX);
	target_pos_a = find_target_pos_in_a(a, b_value);
	cost = get_max(target_pos_a, b_index);
	cost = get_min(cost, get_max(a->size - target_pos_a, b->size - b_index));
	cost = get_min(cost, target_pos_a + (b->size - b_index));
	cost = get_min(cost, (a->size - target_pos_a) + b_index);
	return (cost);
}
