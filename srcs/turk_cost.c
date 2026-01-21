/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:12:51 by toandrad          #+#    #+#             */
/*   Updated: 2026/01/21 13:33:01 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	shared_rotation_cost(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	pick_cheapest(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
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
	cost = shared_rotation_cost(target_pos_a, b_index);
	cost = pick_cheapest(cost, shared_rotation_cost(a->size - target_pos_a,
				b->size - b_index));
	cost = pick_cheapest(cost, target_pos_a + (b->size - b_index));
	cost = pick_cheapest(cost, (a->size - target_pos_a) + b_index);
	return (cost);
}
